#pragma once
#include "decaf_input.h"

#include <common/structsize.h>
#include <common/platform.h>
#include <cstdint>

struct FSClient;

namespace nn
{

namespace swkbd
{

struct AppearArg;
struct KeyboardArg;
struct ControllerInfo;
struct DrawStringInfo;
struct KeyboardCondition;
struct IEventReceiver;
struct ReceiverArg;
struct IControllerEventObj;
struct ISoundObj;

#ifdef PLATFORM_WINDOWS
using swkbd_char_t = int16_t;
#else
using swkbd_char_t = char16_t;
#endif

namespace ControllerType
{
enum Type
{
};
}

namespace RegionType
{
enum Region
{
};
}

namespace State
{
enum State
{
   Hidden = 0,
   FadeIn = 1,
   Visible = 2,
   FadeOut = 3,
   Max = 4,
};
}

bool
AppearInputForm(const AppearArg *arg);

bool
AppearKeyboard(const KeyboardArg *arg);

void
CalcSubThreadFont();

void
CalcSubThreadPredict();

void
Calc(const ControllerInfo *info);

void
ConfirmUnfixAll();

void
Create(unsigned char *,
       RegionType::Region region,
       unsigned int,
       FSClient *fsclient);

void
Destroy();

bool
DisappearInputForm();

bool
DisappearKeyboard();

void
DrawDRC();

void
DrawTV();

void
GetDrawStringInfo(DrawStringInfo *info);

const be_val<swkbd_char_t> *
GetInputFormString();

void
GetKeyboardCondition(KeyboardCondition *condition);

State::State
GetStateInputForm();

State::State
GetStateKeyboard();

void
InactivateSelectCursor();

bool
InitLearnDic(void *dictionary);

bool
IsCoveredWithSubWindow();

bool
IsDecideCancelButton(bool *);

bool
IsDecideOkButton(bool *);

bool
IsKeyboardTarget(const IEventReceiver *receiver);

bool
IsNeedCalcSubThreadFont();

bool
IsNeedCalcSubThreadPredict();

bool
IsSelectCursorActive();

void
MuteAllSound(bool mute);

void
SetControllerRemo(ControllerType::Type controller);

void
SetCursorPos(int32_t pos);

void
SetEnableOkButton(bool enable);

void
SetInputFormString(const be_val<swkbd_char_t> *str);

void
SetReceiver(const ReceiverArg *arg);

void
SetSelectFrom(int32_t pos);

void
SetUserControllerEventObj(IControllerEventObj *obj);

void
SetUserSoundObj(ISoundObj *obj);

void
SetVersion(int32_t version);

namespace internal
{

void
injectTextInput(const char *input);

void
injectKeyInput(decaf::input::KeyboardKey key,
               decaf::input::KeyboardAction action);

} // namespace internal

} // namespace swkbd

} // namespace nn
