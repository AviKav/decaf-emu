#pragma once
#include "ppcutils/va_list.h"
#include "snd_core_constants.h"
#include "snd_core_device.h"
#include "snd_core_enum.h"

#include <common/be_ptr.h>
#include <common/be_val.h>
#include <common/cbool.h>
#include <common/fixed.h>
#include <common/structsize.h>
#include <cstdint>
#include <vector>

namespace snd_core
{

using Pcm16Sample = sg14::make_fixed<15, 0, int16_t>;

using AXVoiceCallbackFn = wfunc_ptr<void*>;
using AXVoiceCallbackExFn = wfunc_ptr<void*, uint32_t, uint32_t>;

#pragma pack(push, 1)

struct AXVoice;

struct AXVoiceLink
{
   be_ptr<AXVoice> next;
   be_ptr<AXVoice> prev;
};
CHECK_OFFSET(AXVoiceLink, 0x0, next);
CHECK_OFFSET(AXVoiceLink, 0x4, prev);
CHECK_SIZE(AXVoiceLink, 0x8);

struct AXVoiceOffsets
{
   be_val<AXVoiceFormat> dataType;
   be_val<AXVoiceLoop> loopingEnabled;
   be_val<uint32_t> loopOffset;
   be_val<uint32_t> endOffset;
   be_val<uint32_t> currentOffset;
   be_ptr<const void> data;
};
CHECK_OFFSET(AXVoiceOffsets, 0x0, dataType);
CHECK_OFFSET(AXVoiceOffsets, 0x2, loopingEnabled);
CHECK_OFFSET(AXVoiceOffsets, 0x4, loopOffset);
CHECK_OFFSET(AXVoiceOffsets, 0x8, endOffset);
CHECK_OFFSET(AXVoiceOffsets, 0xc, currentOffset);
CHECK_OFFSET(AXVoiceOffsets, 0x10, data);
CHECK_SIZE(AXVoiceOffsets, 0x14);

struct AXVoice
{
   //! The index of this voice out of the total voices
   be_val<uint32_t> index;

   //! Current play state of this voice
   be_val<AXVoiceState> state;

   //! Current volume of this voice
   be_val<uint32_t> volume;

   //! The renderer to use for this voice
   be_val<AXRenderer> renderer;

   //! this is a link used in the stack, we do this in host-memory currently
   AXVoiceLink link;

   //! A link to the next callback to invoke
   be_ptr<AXVoice> cbNext;

   //! The priority of this voice used for force-acquiring a voice
   be_val<uint32_t> priority;

   //! The callback to call if this is force-free'd by another acquire
   AXVoiceCallbackFn::be callback;

   //! The user context to send to the callbacks
   be_ptr<void> userContext;

   //! A bitfield representing different things needing to be synced.
   be_val<uint32_t> syncBits;

   UNKNOWN(0x8);

   //! The current offset data!
   AXVoiceOffsets offsets;

   //! An extended version of the callback above
   AXVoiceCallbackExFn::be callbackEx;

   //! The reason for the callback being invoked
   be_val<uint32_t> callbackReason;

   be_val<float> unk0;
   be_val<float> unk1;
};
CHECK_OFFSET(AXVoice, 0x0, index);
CHECK_OFFSET(AXVoice, 0x4, state);
CHECK_OFFSET(AXVoice, 0x8, volume);
CHECK_OFFSET(AXVoice, 0xc, renderer);
CHECK_OFFSET(AXVoice, 0x10, link);
CHECK_OFFSET(AXVoice, 0x18, cbNext);
CHECK_OFFSET(AXVoice, 0x1c, priority);
CHECK_OFFSET(AXVoice, 0x20, callback);
CHECK_OFFSET(AXVoice, 0x24, userContext);
CHECK_OFFSET(AXVoice, 0x28, syncBits);
CHECK_OFFSET(AXVoice, 0x34, offsets);
CHECK_OFFSET(AXVoice, 0x48, callbackEx);
CHECK_OFFSET(AXVoice, 0x4c, callbackReason);
CHECK_OFFSET(AXVoice, 0x50, unk0);
CHECK_OFFSET(AXVoice, 0x54, unk1);
CHECK_SIZE(AXVoice, 0x58);

struct AXVoiceDeviceBusMixData
{
   be_val<uint16_t> volume;
   be_val<int16_t> delta;
};
CHECK_OFFSET(AXVoiceDeviceBusMixData, 0x0, volume);
CHECK_OFFSET(AXVoiceDeviceBusMixData, 0x2, delta);
CHECK_SIZE(AXVoiceDeviceBusMixData, 0x4);

struct AXVoiceDeviceMixData
{
   AXVoiceDeviceBusMixData bus[4];
};
CHECK_OFFSET(AXVoiceDeviceMixData, 0x0, bus);
CHECK_SIZE(AXVoiceDeviceMixData, 0x10);

struct AXVoiceVeData
{
   be_val<uint16_t> volume;
   be_val<int16_t> delta;
};
CHECK_OFFSET(AXVoiceVeData, 0x0, volume);
CHECK_OFFSET(AXVoiceVeData, 0x2, delta);
CHECK_SIZE(AXVoiceVeData, 0x4);

struct AXVoiceAdpcmLoopData
{
   be_val<uint16_t> predScale;
   be_val<int16_t> prevSample[2];
};
CHECK_OFFSET(AXVoiceAdpcmLoopData, 0x0, predScale);
CHECK_OFFSET(AXVoiceAdpcmLoopData, 0x2, prevSample);
CHECK_SIZE(AXVoiceAdpcmLoopData, 0x6);

struct AXVoiceAdpcm
{
   be_val<int16_t> coefficients[16];
   be_val<uint16_t> gain;
   be_val<uint16_t> predScale;
   be_val<int16_t> prevSample[2];
};
CHECK_OFFSET(AXVoiceAdpcm, 0x0, coefficients);
CHECK_OFFSET(AXVoiceAdpcm, 0x20, gain);
CHECK_OFFSET(AXVoiceAdpcm, 0x22, predScale);
CHECK_OFFSET(AXVoiceAdpcm, 0x24, prevSample);
CHECK_SIZE(AXVoiceAdpcm, 0x28);

// Note: "Src" = "sample rate converter", not "source"
struct AXVoiceSrc
{
   // Playback rate
   be_val<ufixed1616_t> ratio;

   // Used by the resampler
   be_val<ufixed016_t> currentOffsetFrac;
   be_val<int16_t> lastSample[4];
};
CHECK_OFFSET(AXVoiceSrc, 0x0, ratio);
CHECK_OFFSET(AXVoiceSrc, 0x4, currentOffsetFrac);
CHECK_OFFSET(AXVoiceSrc, 0x6, lastSample);
CHECK_SIZE(AXVoiceSrc, 0xe);

#pragma pack(pop)

AXVoice *
AXAcquireVoice(uint32_t priority,
               AXVoiceCallbackFn callback,
               void *userContext);

AXVoice *
AXAcquireVoiceEx(uint32_t priority,
                 AXVoiceCallbackExFn callback,
                 void *userContext);

BOOL
AXCheckVoiceOffsets(AXVoiceOffsets *offsets);

void
AXFreeVoice(AXVoice *voice);

uint32_t
AXGetMaxVoices();

uint32_t
AXGetVoiceCurrentOffsetEx(AXVoice *voice,
                          const void *samples);

uint32_t
AXGetVoiceLoopCount(AXVoice *voice);

uint32_t
AXGetVoiceMixerSelect(AXVoice *voice);

void
AXGetVoiceOffsetsEx(AXVoice *voice,
                    AXVoiceOffsets *offsets,
                    const void *samples);

void
AXGetVoiceOffsets(AXVoice *voice,
                  AXVoiceOffsets *offsets);

BOOL
AXIsVoiceRunning(AXVoice *voice);

void
AXSetVoiceAdpcm(AXVoice *voice,
                AXVoiceAdpcm *adpcm);

void
AXSetVoiceAdpcmLoop(AXVoice *voice,
                    AXVoiceAdpcmLoopData *loopData);

void
AXSetVoiceCurrentOffset(AXVoice *voice,
                        uint32_t offset);

void
AXSetVoiceCurrentOffsetEx(AXVoice *voice,
                          uint32_t offset,
                          const void *samples);

AXResult
AXSetVoiceDeviceMix(AXVoice *voice,
                    AXDeviceType type,
                    uint32_t id,
                    AXVoiceDeviceMixData *mixData);

void
AXSetVoiceEndOffset(AXVoice *voice,
                    uint32_t offset);

void
AXSetVoiceEndOffsetEx(AXVoice *voice,
                      uint32_t offset,
                      const void *samples);

AXResult
AXSetVoiceInitialTimeDelay(AXVoice *voice,
                           uint16_t delay);

void
AXSetVoiceLoopOffset(AXVoice *voice,
                     uint32_t offset);

void
AXSetVoiceLoopOffsetEx(AXVoice *voice,
                       uint32_t offset,
                       const void *samples);

void
AXSetVoiceLoop(AXVoice *voice,
               AXVoiceLoop loop);

uint32_t
AXSetVoiceMixerSelect(AXVoice *voice,
                      uint32_t mixerSelect);

void
AXSetVoiceOffsets(AXVoice *voice,
                  AXVoiceOffsets *offsets);

void
AXSetVoiceOffsetsEx(AXVoice *voice,
                    AXVoiceOffsets *offsets,
                    void *samples);

void
AXSetVoicePriority(AXVoice *voice,
                   uint32_t priority);

void
AXSetVoiceRmtOn(AXVoice *voice,
                uint16_t on);

void
AXSetVoiceRmtIIRCoefs(AXVoice *voice,
                      uint16_t filter,
                      ppctypes::VarArgs);

void
AXSetVoiceSrc(AXVoice *voice,
              AXVoiceSrc *src);

AXVoiceSrcRatioResult
AXSetVoiceSrcRatio(AXVoice *voice,
                   float ratio);

void
AXSetVoiceSrcType(AXVoice *voice,
                  AXVoiceSrcType type);

void
AXSetVoiceState(AXVoice *voice,
                AXVoiceState state);

void
AXSetVoiceType(AXVoice *voice,
               AXVoiceType type);

void
AXSetVoiceVe(AXVoice *voice,
             AXVoiceVeData *veData);

void
AXSetVoiceVeDelta(AXVoice *voice,
                  int16_t delta);

namespace internal
{

#pragma pack(push, 1)

struct AXCafeVoiceData
{
   be_val<AXVoiceLoop> loopFlag;
   be_val<AXVoiceFormat> format;
   be_val<uint16_t> memPageNumber;
   be_val<uint32_t> loopOffsetAbs;
   be_val<uint32_t> endOffsetAbs;
   be_val<uint32_t> currentOffsetAbs;
};
CHECK_OFFSET(AXCafeVoiceData, 0x0, loopFlag);
CHECK_OFFSET(AXCafeVoiceData, 0x2, format);
CHECK_OFFSET(AXCafeVoiceData, 0x4, memPageNumber);
CHECK_OFFSET(AXCafeVoiceData, 0x6, loopOffsetAbs);
CHECK_OFFSET(AXCafeVoiceData, 0xa, endOffsetAbs);
CHECK_OFFSET(AXCafeVoiceData, 0xe, currentOffsetAbs);
CHECK_SIZE(AXCafeVoiceData, 0x12);

struct AXCafeVoiceExtras
{
   UNKNOWN(0x8);

   uint16_t srcMode;
   uint16_t srcModeUnk;

   UNKNOWN(0x2);

   AXVoiceType type;

   UNKNOWN(0x15a);

   uint16_t state;

   uint16_t itdOn;

   UNKNOWN(0x2);

   uint16_t itdDelay;

   UNKNOWN(0x8);

   AXVoiceVeData ve;

   AXCafeVoiceData data;

   AXVoiceAdpcm adpcm;

   AXVoiceSrc src;

   AXVoiceAdpcmLoopData adpcmLoop;

   UNKNOWN(0xe4);

   uint32_t syncBits;

   UNKNOWN(0xc);
};
CHECK_OFFSET(AXCafeVoiceExtras, 0x8, srcMode);
CHECK_OFFSET(AXCafeVoiceExtras, 0xa, srcModeUnk);
CHECK_OFFSET(AXCafeVoiceExtras, 0xe, type);
CHECK_OFFSET(AXCafeVoiceExtras, 0x16a, state);
CHECK_OFFSET(AXCafeVoiceExtras, 0x16c, itdOn);
CHECK_OFFSET(AXCafeVoiceExtras, 0x170, itdDelay);
CHECK_OFFSET(AXCafeVoiceExtras, 0x17a, ve);
CHECK_OFFSET(AXCafeVoiceExtras, 0x17e, data);
CHECK_OFFSET(AXCafeVoiceExtras, 0x190, adpcm);
CHECK_OFFSET(AXCafeVoiceExtras, 0x1b8, src);
CHECK_OFFSET(AXCafeVoiceExtras, 0x1c6, adpcmLoop);
CHECK_OFFSET(AXCafeVoiceExtras, 0x2b0, syncBits);
CHECK_SIZE(AXCafeVoiceExtras, 0x2c0);

struct AXVoiceExtras : AXCafeVoiceExtras
{
   struct MixVolume
   {
      ufixed_1_15_t volume;
      ufixed_1_15_t delta;
   };

   // Volume on each of 6 surround channels for TV output
   MixVolume tvVolume[AXNumTvDevices][AXNumTvChannels][AXNumTvBus];

   // Volume on each of 4 channels for DRC output (2 stereo channels + ???)
   MixVolume drcVolume[AXNumDrcDevices][AXNumDrcChannels][AXNumDrcBus];

   // Volume for each of 4 controller speakers
   MixVolume rmtVolume[AXNumRmtDevices][AXNumRmtChannels][AXNumRmtBus];

   // Number of loops so far
   uint32_t loopCount;

   // Used during decoding
   uint32_t numSamples;
   Pcm16Sample samples[144];

};

#pragma pack(pop)

void
initVoices();

void
setVoiceAddresses(AXVoice *voice,
                  AXCafeVoiceData *offsets);

const std::vector<AXVoice*>
getAcquiredVoices();

AXVoiceExtras *
getVoiceExtras(int index);

} // namespace internal

} // namespace snd_core
