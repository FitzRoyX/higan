class Debugger {
public:
  enum BreakEvent {
    None,
    BreakpointHit,
    CPUStep,
    SMPStep,
  } break_event;

  enum { Breakpoints = 8 };
  struct Breakpoint {
    bool enabled;
    unsigned addr;
    signed data;  //-1 = unused
    enum Mode { Exec, Read, Write } mode;
    enum Source { CPUBus, APURAM, VRAM, OAM, CGRAM } source;
    unsigned counter;  //number of times breakpoint has been hit since being set
  } breakpoint[Breakpoints];
  unsigned breakpoint_hit;

  bool step_cpu;
  bool step_smp;

  file tracefile;
  bool trace_cpu;
  bool trace_smp;

  enum MemorySource { CPUBus, APURAM, VRAM, OAM, CGRAM };
  uint8 read(MemorySource, unsigned addr);

  Debugger();
};

extern Debugger debugger;