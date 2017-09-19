#include "decaf_config.h"
#include "gx2.h"
#include "gx2_debug.h"
#include "gx2_enum_string.h"
#include "gx2_internal_cbpool.h"
#include "gx2_internal_gfd.h"
#include "gx2_shaders.h"
#include "gx2_texture.h"
#include "modules/coreinit/coreinit_sprintf.h"
#include "ppcutils/va_list.h"

#include <fstream>
#include <common/align.h>
#include <common/log.h>
#include <common/platform_dir.h>
#include <fmt/format.h>
#include <libcpu/mem.h>
#include <libgpu/latte/latte_disassembler.h>
#include <libgfd/gfd.h>

namespace gx2
{

void
GX2DebugTagUserString(uint32_t unk,
                      const char *fmt,
                      ppctypes::VarArgs)
{
   auto list = ppctypes::make_va_list(2, 0);
   GX2DebugTagUserStringVA(unk, fmt, list);
   ppctypes::free_va_list(list);
}

void
GX2DebugTagUserStringVA(uint32_t unk,
                        const char *fmt,
                        ppctypes::va_list *list)
{
   char buffer[0x404];
   std::memset(buffer, 0, 0x404);

   if (fmt) {
      coreinit::internal::formatStringV(buffer, 0x3FF, fmt, list);
   }

   // Convert string to words!
   auto length = static_cast<uint32_t>(strlen(buffer));
   auto words = align_up(length + 1, 4) / 4;

   std::vector<uint32_t> strWords;
   strWords.resize(words, 0);
   std::memcpy(strWords.data(), buffer, length);

   // Write NOP packet
   internal::writePM4(latte::pm4::Nop {
      unk,
      gsl::make_span(strWords)
   });
}

namespace internal
{

static void
createDumpDirectory()
{
   platform::createDirectory("dump");
}

static std::string
pointerAsString(const void *pointer)
{
   fmt::MemoryWriter format;
   format.write("{:08X}", mem::untranslate(pointer));
   return format.str();
}

static void
debugDumpData(const std::string &filename, const void *data, size_t size)
{
   auto file = std::ofstream { filename, std::ofstream::out | std::ofstream::binary };
   file.write(static_cast<const char *>(data), size);
   file.close();
}

static void
debugDumpData(std::ofstream &file, const void *data, size_t size)
{
   file.write(reinterpret_cast<const char *>(data), size);
}

void
debugDumpTexture(const GX2Texture *texture)
{
   if (!decaf::config::gx2::dump_textures) {
      return;
   }

   createDumpDirectory();

   // Write text dump of GX2Texture structure to texture_X.txt
   auto filename = "texture_" + pointerAsString(texture);

   if (platform::fileExists("dump/" + filename + ".txt")) {
      return;
   }

   auto file = std::ofstream { "dump/" + filename + ".txt", std::ofstream::out };
   auto format = fmt::MemoryWriter {};

   format
      << "surface.dim = " << gx2::to_string(texture->surface.dim) << '\n'
      << "surface.width = " << texture->surface.width << '\n'
      << "surface.height = " << texture->surface.height << '\n'
      << "surface.depth = " << texture->surface.depth << '\n'
      << "surface.mipLevels = " << texture->surface.mipLevels << '\n'
      << "surface.format = " << gx2::to_string(texture->surface.format) << '\n'
      << "surface.aa = " << gx2::to_string(texture->surface.aa) << '\n'
      << "surface.use = " << gx2::to_string(texture->surface.use) << '\n'
      << "surface.resourceFlags = " << texture->surface.resourceFlags << '\n'
      << "surface.imageSize = " << texture->surface.imageSize << '\n'
      << "surface.image = " << pointerAsString(texture->surface.image) << '\n'
      << "surface.mipmapSize = " << texture->surface.mipmapSize << '\n'
      << "surface.mipmaps = " << pointerAsString(texture->surface.mipmaps) << '\n'
      << "surface.tileMode = " << gx2::to_string(texture->surface.tileMode) << '\n'
      << "surface.swizzle = " << texture->surface.swizzle << '\n'
      << "surface.alignment = " << texture->surface.alignment << '\n'
      << "surface.pitch = " << texture->surface.pitch << '\n'
      << "viewFirstMip = " << texture->viewFirstMip << '\n'
      << "viewNumMips = " << texture->viewNumMips << '\n'
      << "viewFirstSlice = " << texture->viewFirstSlice << '\n'
      << "viewNumSlices = " << texture->viewNumSlices << '\n';

   file << format.str();

   if (!texture->surface.image || !texture->surface.imageSize) {
      return;
   }

   // Write GTX file
   gfd::GFDFile gtx;
   gfd::GFDTexture gfdTexture;
   gx2ToGFDTexture(texture, gfdTexture);
   gtx.textures.push_back(gfdTexture);
   gfd::writeFile(gtx, "dump/" + filename + ".gtx");
}

static void
addShader(gfd::GFDFile &file, GX2VertexShader *shader)
{
   gfd::GFDVertexShader gfdShader;
   gx2ToGFDVertexShader(shader, gfdShader);
   file.vertexShaders.emplace_back(std::move(gfdShader));
}

static void
addShader(gfd::GFDFile &file, GX2PixelShader *shader)
{
   gfd::GFDPixelShader gfdShader;
   gx2ToGFDPixelShader(shader, gfdShader);
   file.pixelShaders.emplace_back(std::move(gfdShader));
}

static void
addShader(gfd::GFDFile &file, GX2GeometryShader *shader)
{
   gfd::GFDGeometryShader gfdShader;
   gx2ToGFDGeometryShader(shader, gfdShader);
   file.geometryShaders.emplace_back(std::move(gfdShader));
}

static void
addShader(gfd::GFDFile &file, GX2FetchShader *shader)
{
   // TODO: Add FetchShader support to .gsh
}

template<typename ShaderType>
static void
debugDumpShader(const std::string &filename,
                const std::string &info,
                ShaderType *shader,
                bool isSubroutine = false)
{
   std::string output;

   // Write binary of shader data to shader_pixel_X.bin
   createDumpDirectory();

   if (platform::fileExists("dump/" + filename + ".bin")) {
      return;
   }

   gLog->debug("Dumping shader {}", filename);
   debugDumpData("dump/" + filename + ".bin", shader->data, shader->size);

   // Write GSH file
   gfd::GFDFile gsh;
   addShader(gsh, shader);
   gfd::writeFile(gsh, "dump/" + filename + ".gsh");

   // Write text of shader to shader_pixel_X.txt
   auto file = std::ofstream { "dump/" + filename + ".txt", std::ofstream::out };

   // Disassemble
   output = latte::disassemble(gsl::make_span(shader->data.get(), shader->size), isSubroutine);

   file
      << info << std::endl
      << "Disassembly:" << std::endl
      << output << std::endl;
}

static void
formatUniformBlocks(fmt::MemoryWriter &out, uint32_t count, GX2UniformBlock *blocks)
{
   out << "  uniformBlockCount: " << count << "\n";

   for (auto i = 0u; i < count; ++i) {
      out << "    Block " << i << "\n"
         << "      name: " << blocks[i].name.get() << "\n"
         << "      offset: " << blocks[i].offset << "\n"
         << "      size: " << blocks[i].size << "\n";
   }
}

static void
formatAttribVars(fmt::MemoryWriter &out, uint32_t count, GX2AttribVar *vars)
{
   out << "  attribVarCount: " << count << "\n";

   for (auto i = 0u; i < count; ++i) {
      out << "    Var " << i << "\n"
         << "      name: " << vars[i].name.get() << "\n"
         << "      type: " << gx2::to_string(vars[i].type) << "\n"
         << "      count: " << vars[i].count << "\n"
         << "      location: " << vars[i].location << "\n";
   }
}

static void
formatInitialValues(fmt::MemoryWriter &out, uint32_t count, GX2UniformInitialValue *vars)
{
   out << "  intialValueCount: " << count << "\n";

   for (auto i = 0u; i < count; ++i) {
      out << "    Var " << i << "\n"
         << "      offset: " << vars[i].offset << "\n"
         << "      value: ("
            << vars[i].value[0] << ", "
            << vars[i].value[1] << ", "
            << vars[i].value[2] << ", "
            << vars[i].value[3] << ")"
            << "\n";
   }
}

static void
formatLoopVars(fmt::MemoryWriter &out, uint32_t count, GX2LoopVar *vars)
{
   out << "  loopVarCount: " << count << "\n";

   for (auto i = 0u; i < count; ++i) {
      out << "    Var " << i << "\n"
         << "      value: " << vars[i].value << "\n"
         << "      offset: " << vars[i].offset << "\n";
   }
}

static void
formatUniformVars(fmt::MemoryWriter &out, uint32_t count, GX2UniformVar *vars)
{
   out << "  uniformVarCount: " << count << "\n";

   for (auto i = 0u; i < count; ++i) {
      out << "    Var " << i << "\n"
         << "      name: " << vars[i].name.get() << "\n"
         << "      type: " << gx2::to_string(vars[i].type) << "\n"
         << "      count: " << vars[i].count << "\n"
         << "      offset: " << vars[i].offset << "\n"
         << "      block: " << vars[i].block << "\n";
   }
}

static void
formatSamplerVars(fmt::MemoryWriter &out, uint32_t count, GX2SamplerVar *vars)
{
   out << "  samplerVarCount: " << count << "\n";

   for (auto i = 0u; i < count; ++i) {
      out << "    Var " << i << "\n"
         << "      name: " << vars[i].name.get() << "\n"
         << "      type: " << gx2::to_string(vars[i].type) << "\n"
         << "      location: " << vars[i].location << "\n";
   }
}

void
debugDumpShader(GX2FetchShader *shader)
{
   if (!decaf::config::gx2::dump_shaders) {
      return;
   }

   fmt::MemoryWriter out;
   out << "GX2FetchShader:\n"
      << "  address: " << fmt::format("0x{:X}", shader->data.getAddress()) << "\n"
      << "  size: " << shader->size << "\n";

   debugDumpShader("shader_fetch_" + pointerAsString(shader),
                   out.str(),
                   shader,
                   true);
}

void
debugDumpShader(GX2PixelShader *shader)
{
   if (!decaf::config::gx2::dump_shaders) {
      return;
   }

   fmt::MemoryWriter out;
   out << "GX2PixelShader:\n"
      << "  address: " << fmt::format("0x{:X}", shader->data.getAddress()) << "\n"
      << "  size: " << shader->size << "\n"
      << "  mode: " << gx2::to_string(shader->mode) << "\n";

   formatUniformBlocks(out, shader->uniformBlockCount, shader->uniformBlocks);
   formatUniformVars(out, shader->uniformVarCount, shader->uniformVars);
   formatInitialValues(out, shader->initialValueCount, shader->initialValues);
   formatLoopVars(out, shader->loopVarCount, shader->loopVars);
   formatSamplerVars(out, shader->samplerVarCount, shader->samplerVars);

   debugDumpShader("shader_pixel_" + pointerAsString(shader),
                   out.str(),
                   shader);
}

void
debugDumpShader(GX2VertexShader *shader)
{
   if (!decaf::config::gx2::dump_shaders) {
      return;
   }

   fmt::MemoryWriter out;
   out << "GX2VertexShader:\n"
      << "  address: " << fmt::format("0x{:X}", shader->data.getAddress()) << "\n"
      << "  size: " << shader->size << "\n"
      << "  mode: " << gx2::to_string(shader->mode) << "\n";

   formatUniformBlocks(out, shader->uniformBlockCount, shader->uniformBlocks);
   formatUniformVars(out, shader->uniformVarCount, shader->uniformVars);
   formatInitialValues(out, shader->initialValueCount, shader->initialValues);
   formatLoopVars(out, shader->loopVarCount, shader->loopVars);
   formatSamplerVars(out, shader->samplerVarCount, shader->samplerVars);
   formatAttribVars(out, shader->attribVarCount, shader->attribVars);

   debugDumpShader("shader_vertex_" + pointerAsString(shader),
                   out.str(),
                   shader);
}

void writeDebugMarker(const char *key, uint32_t id)
{
   gLog->trace("CPU Debug Marker: {} {}", key, id);

   // PM4 commands must be 32 bit aligned, we need to copy it
   //  to a temporary local buffer so the gsl span doesn't
   //  overrun the variable which was passed by the user.
   static char tmpBuf[128];
   auto strLen = strlen(key) + 1;
   auto alignedStrLen = align_up(strLen, 4);
   memset(tmpBuf, 0, 128);
   memcpy(tmpBuf, key, strLen);

   internal::writePM4(latte::pm4::DecafDebugMarker {
      id,
      gsl::make_span(tmpBuf, alignedStrLen),
   });
}

} // namespace internal

} // namespace gx2
