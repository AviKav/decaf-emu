#ifndef COREINIT_ENUM_H
#define COREINIT_ENUM_H

#include <common/enum_start.h>

ENUM_NAMESPACE_BEG(cafe)
ENUM_NAMESPACE_BEG(coreinit)

ENUM_BEG(BSPError, uint32_t)
   ENUM_VALUE(OK,                0)
   ENUM_VALUE(IosError,          0x40)
   ENUM_VALUE(ResponseTooLarge,  0x80)
ENUM_END(BSPError)

ENUM_BEG(COSReportLevel, uint32_t)
   ENUM_VALUE(Error,             0)
   ENUM_VALUE(Warn,              1)
   ENUM_VALUE(Info,              2)
   ENUM_VALUE(Verbose,           3)
ENUM_END(COSReportLevel)

ENUM_BEG(COSReportModule, uint32_t)
   ENUM_VALUE(Unknown0,          0)
   ENUM_VALUE(Unknown1,          1)
   ENUM_VALUE(Unknown2,          2)
   ENUM_VALUE(Unknown5,          5)
ENUM_END(COSReportModule)

ENUM_BEG(IPCDriverStatus, uint32_t)
   ENUM_VALUE(Closed,               1)
   ENUM_VALUE(Initialised,          2)
   ENUM_VALUE(Open,                 3)
ENUM_END(IPCDriverStatus)

ENUM_BEG(OSAlarmState, uint32_t)
   ENUM_VALUE(Idle,                 0)
   ENUM_VALUE(Set,                  1)
   ENUM_VALUE(Expired,              2)
   ENUM_VALUE(Invalid,              0x79646CFF)
ENUM_END(OSAlarmState)

ENUM_BEG(OSAppFlagsDebugLevel, uint32_t)
   ENUM_VALUE(Error,                0)
   ENUM_VALUE(Warn,                 1)
   ENUM_VALUE(Info,                 2)
   ENUM_VALUE(Unknown3,             3)
   ENUM_VALUE(Verbose,              7)
ENUM_END(OSAppFlagsDebugLevel)

ENUM_BEG(OSDeviceID, uint32_t)
   ENUM_VALUE(VI,                   0)
   ENUM_VALUE(DSP,                  1)
   ENUM_VALUE(GFXSP,                2)
   ENUM_VALUE(SI,                   6)
   ENUM_VALUE(LATTE_REGS,           11)
   ENUM_VALUE(LEGACY_SI,            12)
   ENUM_VALUE(LEGACY_AI_I2S3,       13)
   ENUM_VALUE(LEGACY_AI_I2S5,       14)
   ENUM_VALUE(LEGACY_EXI,           15)
ENUM_END(OSDeviceID)

ENUM_BEG(OSDriver_Error, uint32_t)
   ENUM_VALUE(OK,                   0)
   ENUM_VALUE(DriverNotFound,       0xBAD70002)
   ENUM_VALUE(InvalidArgument,      0xBAD70003)
   ENUM_VALUE(OutOfSysMemory,       0xBAD70004)
   ENUM_VALUE(AlreadyRegistered,    0xBAD70005)
ENUM_END(OSDriver_Error)

ENUM_BEG(OSDynLoad_Error, uint32_t)
   ENUM_VALUE(OK,                      0)
   ENUM_VALUE(OutOfMemory,             0xBAD10002)
   ENUM_VALUE(InvalidHandle,           0xBAD10003)
   ENUM_VALUE(InvalidRPL,              0xBAD1000C)
   ENUM_VALUE(InvalidNotifyPtr,        0xBAD1000E)
   ENUM_VALUE(InvalidModuleNamePtr,    0xBAD1000F)
   ENUM_VALUE(InvalidModuleName,       0xBAD10010)
   ENUM_VALUE(InvalidAcquirePtr,       0xBAD10011)
   ENUM_VALUE(EmptyModuleName,         0xBAD10012)
   ENUM_VALUE(InvalidAllocatedPtr,     0xBAD10014)
   ENUM_VALUE(InModuleEntryPoint,      0xBAD10016)
   ENUM_VALUE(InvalidAllocatorPtr,     0xBAD10017)
   ENUM_VALUE(ModuleHasNoDataExports,  0xBAD1001B)
   ENUM_VALUE(ModuleHasNoCodeExports,  0xBAD1001C)
   ENUM_VALUE(ExportNotFound,          0xBAD1001D)
   ENUM_VALUE(InvalidParam,            0xBAD1001E)
   ENUM_VALUE(BufferTooSmall,          0xBAD1001F)
   ENUM_VALUE(LoaderError,             0xBAD10021)
   ENUM_VALUE(ModuleNotFound,          0xBAD10023)
   ENUM_VALUE(InvalidContainPtr,       0xBAD10027)
   ENUM_VALUE(ContainModuleNotFound,   0xBAD10028)
   ENUM_VALUE(RunEntryPointError,      0xBAD10029)
   ENUM_VALUE(OutOfSysMemory,          0xBAD1002F)
   ENUM_VALUE(TLSAllocatorLocked,      0xBAD10031)
   ENUM_VALUE(TLSTooManyModules,       0xBAD10032)
   ENUM_VALUE(TLSFindExportInvalid,    0xBAD10033)
   ENUM_VALUE(InvalidShStrNdx,         0xBAD1003A)
   ENUM_VALUE(InvalidShStrSection,     0xBAD1003B)
   ENUM_VALUE(TLSSectionNotFound,      0xBAD1003D)
   ENUM_VALUE(InvalidRpxEntryPoint,    0xBAD1003E)
ENUM_END(OSDynLoad_Error)

ENUM_BEG(OSDynLoad_EntryReason, uint32_t)
   ENUM_VALUE(Loaded,               1)
   ENUM_VALUE(Unloaded,             2)
ENUM_END(OSDynLoad_EntryReason)

ENUM_BEG(OSDynLoad_NotifyEvent, uint32_t)
   ENUM_VALUE(Unloaded,             0)
   ENUM_VALUE(Loaded,               1)
ENUM_END(OSDynLoad_NotifyEvent)

ENUM_BEG(OSDynLoad_SectionType, uint32_t)
   ENUM_VALUE(Any,                  0)
   ENUM_VALUE(CodeOnly,             1)
   ENUM_VALUE(DataOnly,             2)
ENUM_END(OSDynLoad_SectionType)

ENUM_BEG(OSEventMode, uint32_t)
   //! A manual event will only reset when OSResetEvent is called.
   ENUM_VALUE(ManualReset,          0)

   //! An auto event will reset everytime a thread is woken.
   ENUM_VALUE(AutoReset,            1)
ENUM_END(OSEventMode)

ENUM_BEG(OSExceptionMode, uint32_t)
   ENUM_VALUE(System,               0)
   ENUM_VALUE(Thread,               1)
   ENUM_VALUE(Global,               2)
   ENUM_VALUE(ThreadAllCores,       3)
   ENUM_VALUE(GlobalAllCores,       4)
ENUM_END(OSExceptionMode)

ENUM_BEG(OSExceptionType, uint32_t)
   ENUM_VALUE(SystemReset,          0)
   ENUM_VALUE(MachineCheck,         1)
   ENUM_VALUE(DSI,                  2)
   ENUM_VALUE(ISI,                  3)
   ENUM_VALUE(ExternalInterrupt,    4)
   ENUM_VALUE(Alignment,            5)
   ENUM_VALUE(Program,              6)
   ENUM_VALUE(FloatingPoint,        7)
   ENUM_VALUE(Decrementer,          8)
   ENUM_VALUE(SystemCall,           9)
   ENUM_VALUE(Trace,                10)
   ENUM_VALUE(PerformanceMonitor,   11)
   ENUM_VALUE(Breakpoint,           12)
   ENUM_VALUE(SystemInterrupt,      13)
   ENUM_VALUE(ICI,                  14)
   ENUM_VALUE(Max,                  15)
ENUM_END(OSExceptionType)

ENUM_BEG(OSFunctionType, uint32_t)
   ENUM_VALUE(HioOpen,              1)
   ENUM_VALUE(HioReadAsync,         2)
   ENUM_VALUE(HioWriteAsync,        3)
   ENUM_VALUE(FsaCmdAsync,          4)
   ENUM_VALUE(FsaPrCmdAsync,        5)
   ENUM_VALUE(FsaPrCmdAsyncNoAlloc, 6)
   ENUM_VALUE(FsaAttachEvent,       7)
   ENUM_VALUE(FsCmdAsync,           8)
   ENUM_VALUE(FsCmdHandler,         9)
   ENUM_VALUE(FsAttachEvent,        10)
   ENUM_VALUE(FsStateChangeEvent,   11)
ENUM_END(OSFunctionType)

ENUM_BEG(OSHandleError, uint32_t)
   ENUM_VALUE(OK,       0)
   ENUM_VALUE(InvalidArgument,      0xBAD50002)
   ENUM_VALUE(InvalidHandle,        0xBAD50004)
   ENUM_VALUE(TableFull,            0xBAD50005)
   ENUM_VALUE(InternalError,        0xBAD50006)
ENUM_END(OSHandleError)

ENUM_BEG(OSMapMemoryPermission, uint32_t)
   ENUM_VALUE(ReadOnly,             0x1)
   ENUM_VALUE(ReadWrite,            0x2)
ENUM_END(OSMapMemoryPermission)

ENUM_BEG(OSMemoryType, uint32_t)
   ENUM_VALUE(MEM1,                 1)
   ENUM_VALUE(MEM2,                 2)
ENUM_END(OSMemoryType)

FLAGS_BEG(OSMessageFlags, uint32_t)
   FLAGS_VALUE(None,                0)
   FLAGS_VALUE(Blocking,            1 << 0)
   FLAGS_VALUE(HighPriority,        1 << 1)
FLAGS_END(OSMessageFlags)

ENUM_BEG(OSSharedDataType, uint32_t)
   ENUM_VALUE(FontChinese,          0)
   ENUM_VALUE(FontKorean,           1)
   ENUM_VALUE(FontStandard,         2)
   ENUM_VALUE(FontTaiwanese,        3)
   ENUM_VALUE(Max,                  4)
ENUM_END(OSSharedDataType)

ENUM_BEG(OSShutdownReason, uint32_t)
   ENUM_VALUE(NoShutdown,           0)
ENUM_END(OSShutdownReason)

FLAGS_BEG(OSThreadAttributes, uint8_t)
   //! Allow the thread to run on CPU0.
   FLAGS_VALUE(AffinityCPU0,        1 << 0)

   //! Allow the thread to run on CPU1.
   FLAGS_VALUE(AffinityCPU1,        1 << 1)

   //! Allow the thread to run on CPU2.
   FLAGS_VALUE(AffinityCPU2,        1 << 2)

   //! Allow the thread to run any CPU.
   FLAGS_VALUE(AffinityAny,         (1 << 0) | (1 << 1) | (1 << 2))

   //! Start the thread detached.
   FLAGS_VALUE(Detached,            1 << 3)

   //! Enables tracking of stack usage.
   FLAGS_VALUE(StackUsage,          1 << 5)
FLAGS_END(OSThreadAttributes)

FLAGS_BEG(OSThreadCancelState, uint32_t)
   //! Thread cancel is enabled
   FLAGS_VALUE(Enabled,                      0)

   //! Thread cancel is disabled by OSSetThreadCancelState
   FLAGS_VALUE(Disabled,                     1 << 0)

   //! Thread cancel is disabled because the thread owns a mutex
   FLAGS_VALUE(DisabledByMutex,              1 << 16)

   //! Thread cancel is disabled because the thread owns an uninterruptible spinlock
   FLAGS_VALUE(DisabledBySpinlock,           1 << 17)

   //! Thread cancel is disabled because the thread has a user stack pointer
   FLAGS_VALUE(DisabledByUserStackPointer,   1 << 18)

   //! Thread cancel is disabled because the thread owns a fast mutex
   FLAGS_VALUE(DisabledByFastMutex,          1 << 19)
FLAGS_END(OSThreadCancelState)

ENUM_BEG(OSThreadQuantum, uint32_t)
   ENUM_VALUE(Infinite,             0)
   ENUM_VALUE(MinMicroseconds,      10)
   ENUM_VALUE(MaxMicroseconds,      0xFFFFF)
ENUM_END(OSThreadQuantum)

ENUM_BEG(OSThreadRequest, uint32_t)
   ENUM_VALUE(None,                 0)
   ENUM_VALUE(Suspend,              1)
   ENUM_VALUE(Cancel,               2)
ENUM_END(OSThreadRequest)

FLAGS_BEG(OSThreadState, uint8_t)
   FLAGS_VALUE(None,                0)

   //! Thread is ready to run
   FLAGS_VALUE(Ready,               1 << 0)

   //! Thread is running
   FLAGS_VALUE(Running,             1 << 1)

   //! Thread is waiting, i.e. on a mutex
   FLAGS_VALUE(Waiting,             1 << 2)

   //! Thread is about to terminate
   FLAGS_VALUE(Moribund,            1 << 3)
FLAGS_END(OSThreadState)

ENUM_BEG(OSThreadType, uint32_t)
   ENUM_VALUE(Driver,               0)
   ENUM_VALUE(AppIo,                1)
   ENUM_VALUE(App,                  2)
ENUM_END(OSThreadType)

ENUM_BEG(FSAIpcRequestType, uint16_t)
   ENUM_VALUE(Ioctl,                   0)
   ENUM_VALUE(Ioctlv,                  1)
ENUM_END(FSAIpcRequestType)

ENUM_BEG(FSCmdBlockStatus, uint32_t)
   ENUM_VALUE(Initialised,             0xD900A21)
   ENUM_VALUE(QueuedCommand,           0xD900A22)
   ENUM_VALUE(DeqeuedCommand,          0xD900A23)
   ENUM_VALUE(Cancelled,               0xD900A24)
   ENUM_VALUE(Completed,               0xD900A26)
ENUM_END(FSCmdBlockStatus)

ENUM_BEG(FSCmdCancelFlags, uint32_t)
   ENUM_VALUE(None,                    0)
   ENUM_VALUE(Cancelling,              1)
ENUM_END(FSCmdCancelFlags)

FLAGS_BEG(FSCmdQueueStatus, uint32_t)
   FLAGS_VALUE(MaxActiveCommands,       1)
   FLAGS_VALUE(Suspended,               1 << 4)
FLAGS_END(FSCmdQueueStatus)

FLAGS_BEG(FSErrorFlag, uint32_t)
   FLAGS_VALUE(None,                    0x0)
   FLAGS_VALUE(Max,                     0x1)
   FLAGS_VALUE(AlreadyOpen,             0x2)
   FLAGS_VALUE(Exists,                  0x4)
   FLAGS_VALUE(NotFound,                0x8)
   FLAGS_VALUE(NotFile,                 0x10)
   FLAGS_VALUE(NotDir,                  0x20)
   FLAGS_VALUE(AccessError,             0x40)
   FLAGS_VALUE(PermissionError,         0x80)
   FLAGS_VALUE(FileTooBig,              0x100)
   FLAGS_VALUE(StorageFull,             0x200)
   FLAGS_VALUE(UnsupportedCmd,          0x400)
   FLAGS_VALUE(JournalFull,             0x800)
   FLAGS_VALUE(All,                     0xFFFFFFFF)
FLAGS_END(FSErrorFlag)

ENUM_BEG(FSMountSourceType, uint32_t)
   ENUM_VALUE(SdCard,                  0)
   ENUM_VALUE(HostFileIO,              1)
   ENUM_VALUE(Bind,                    2)
ENUM_END(FSMountSourceType)

ENUM_BEG(FSStatus, int32_t)
   ENUM_VALUE(OK,                   0)
   ENUM_VALUE(Cancelled,            -1)
   ENUM_VALUE(End,                  -2)
   ENUM_VALUE(Max,                  -3)
   ENUM_VALUE(AlreadyOpen,          -4)
   ENUM_VALUE(Exists,               -5)
   ENUM_VALUE(NotFound,             -6)
   ENUM_VALUE(NotFile,              -7)
   ENUM_VALUE(NotDirectory,         -8)
   ENUM_VALUE(AccessError,          -9)
   ENUM_VALUE(PermissionError,      -10)
   ENUM_VALUE(FileTooBig,           -11)
   ENUM_VALUE(StorageFull,          -12)
   ENUM_VALUE(JournalFull,          -13)
   ENUM_VALUE(UnsupportedCmd,       -14)
   ENUM_VALUE(MediaNotReady,        -15)
   ENUM_VALUE(MediaError,           -17)
   ENUM_VALUE(Corrupted,            -18)
   ENUM_VALUE(FatalError,           -0x400)
ENUM_END(FSStatus)

ENUM_BEG(FSVolumeState, uint32_t)
   ENUM_VALUE(Initial,              0)
   ENUM_VALUE(Ready,                1)
   ENUM_VALUE(NoMedia,              2)
   ENUM_VALUE(InvalidMedia,         3)
   ENUM_VALUE(DirtyMedia,           4)
   ENUM_VALUE(WrongMedia,           5)
   ENUM_VALUE(MediaError,           6)
   ENUM_VALUE(DataCorrupted,        7)
   ENUM_VALUE(WriteProtected,       8)
   ENUM_VALUE(JournalFull,          9)
   ENUM_VALUE(Fatal,                10)
   ENUM_VALUE(Invalid,              11)
ENUM_END(FSVolumeState)

ENUM_BEG(GHSSyscallID, uint32_t)
   ENUM_VALUE(time,                 0x0000E)
   ENUM_VALUE(close,                0x20005)
   ENUM_VALUE(unlink,               0x20008)
   ENUM_VALUE(system,               0x2000A)
   ENUM_VALUE(creat,                0x30006)
   ENUM_VALUE(access,               0x3000B)
   ENUM_VALUE(read,                 0x40000)
   ENUM_VALUE(write,                0x40001)
   ENUM_VALUE(open,                 0x40004)
   ENUM_VALUE(lseek,                0x40007)
   ENUM_VALUE(fnctl,                0x40012)
   ENUM_VALUE(fstat,                0x40018)
   ENUM_VALUE(stat,                 0x40019)
ENUM_END(GHSSyscallID)

ENUM_BEG(MEMBaseHeapType, uint32_t)
   ENUM_VALUE(MEM1,                 0)
   ENUM_VALUE(MEM2,                 1)
   ENUM_VALUE(FG,                   8)
   ENUM_VALUE(Max,                  9)
   ENUM_VALUE(Invalid,              10)
ENUM_END(MEMBaseHeapType)

ENUM_BEG(MEMExpHeapMode, uint32_t)
   ENUM_VALUE(FirstFree,            0)
   ENUM_VALUE(NearestSize,          1)
ENUM_END(MEMExpHeapMode)

ENUM_BEG(MEMExpHeapDirection, uint32_t)
   ENUM_VALUE(FromStart,            0)
   ENUM_VALUE(FromEnd,              1)
ENUM_END(MEMExpHeapDirection)

FLAGS_BEG(MEMFrameHeapFreeMode, uint32_t)
   FLAGS_VALUE(Head,                1 << 0)
   FLAGS_VALUE(Tail,                1 << 1)
FLAGS_END(MEMFrameHeapFreeMode)

ENUM_BEG(MEMHeapTag, uint32_t)
   ENUM_VALUE(ExpandedHeap,         0x45585048)
   ENUM_VALUE(FrameHeap,            0x46524D48)
   ENUM_VALUE(UnitHeap,             0x554E5448)
   ENUM_VALUE(UserHeap,             0x55535248)
   ENUM_VALUE(BlockHeap,            0x424C4B48)
ENUM_END(MEMHeapTag)

ENUM_BEG(MEMHeapFillType, uint32_t)
   ENUM_VALUE(Unused,               0x0)
   ENUM_VALUE(Allocated,            0x1)
   ENUM_VALUE(Freed,                0x2)
   ENUM_VALUE(Max,                  0x3)
ENUM_END(MEMHeapFillType)

FLAGS_BEG(MEMHeapFlags, uint32_t)
   FLAGS_VALUE(None,                0)
   FLAGS_VALUE(ZeroAllocated,       1 << 0)
   FLAGS_VALUE(DebugMode,           1 << 1)
   FLAGS_VALUE(ThreadSafe,          1 << 2)
FLAGS_END(MEMHeapFlags)

FLAGS_BEG(MPTaskQueueState, uint32_t)
   FLAGS_VALUE(Initialised,         1 << 0)
   FLAGS_VALUE(Ready,               1 << 1)
   FLAGS_VALUE(Stopping,            1 << 2)
   FLAGS_VALUE(Stopped,             1 << 3)
   FLAGS_VALUE(Finished,            1 << 4)
FLAGS_END(MPTaskQueueState)

FLAGS_BEG(MPTaskState, uint32_t)
   FLAGS_VALUE(Initialised,         1 << 0)
   FLAGS_VALUE(Ready,               1 << 1)
   FLAGS_VALUE(Running,             1 << 2)
   FLAGS_VALUE(Finished,            1 << 3)
FLAGS_END(MPTaskState)

ENUM_BEG(SIRegisters, uint32_t)
   ENUM_VALUE(Controller0Command,   0)
   ENUM_VALUE(Controller0Status0,   1)
   ENUM_VALUE(Controller0Status1,   2)
   ENUM_VALUE(Controller1Command,   3)
   ENUM_VALUE(Controller1Status0,   4)
   ENUM_VALUE(Controller1Status1,   5)
   ENUM_VALUE(Controller2Command,   6)
   ENUM_VALUE(Controller2Status0,   7)
   ENUM_VALUE(Controller2Status1,   8)
   ENUM_VALUE(Controller3Command,   9)
   ENUM_VALUE(Controller3Status0,   10)
   ENUM_VALUE(Controller3Status1,   11)
   ENUM_VALUE(PollControl,          12)
   ENUM_VALUE(DeviceStatus,         13)
   ENUM_VALUE(ControllerError,      14)
ENUM_END(SIRegisters)

ENUM_NAMESPACE_END(coreinit)
ENUM_NAMESPACE_END(cafe)

#include <common/enum_end.h>

#endif // ifdef COREINIT_ENUM_H
