#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
  PIC1 = 0x20,
  PIC2 = 0xA0,
} pic_port_t;

typedef struct {
  unsigned int gs, fs, es, ds;
  unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
  unsigned int interrupt, error;
  unsigned int eip, cs, eflags, uresp, ss;
} __attribute__((packed)) irq_state_t;

typedef int (*irq_handler_t) (irq_state_t* s);

extern void gdt_install();
extern void idt_install();
extern void idt_set_gate(
  size_t gate,
  uint32_t offset,
  uint16_t selector,
  bool present,
  uint8_t dpl,
  bool is_task,
  uint8_t type
);
extern void pic_ack(size_t irq);
extern void irq_install();
extern void irq_install_handler(size_t irq, irq_handler_t handler);