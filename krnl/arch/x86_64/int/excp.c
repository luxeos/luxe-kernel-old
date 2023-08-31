/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/pic/pic.h>
#include <int/excp.h>
#include <int/idt.h>

#include <luxe.h>

static const char *g_exception_str[32] = {
	"division by zero",
	"debug",
	"nonmaskable interrupt",
	"breakpoint",
	"overflow",
	"bound range exceeded",
	"invalid opcode",
	"device not available",
	"double fault",
	"coprocessor segment overrun",
	"invalid tss",
	"segment not present",
	"stack segment fault",
	"general protection fault",
	"page fault",
	"reserved",
	"x87 fpu error"
	"alignment check",
	"machine check",
	"simd exception",
	"virtualization exception",
	"control protection exception",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"reserved",
	"hypervisor injection exception",
	"vmm communication exception",
	"security exception",
	"reserved"
};

void excp_handler(int_frame_t frame)
{
	if (frame.vector < 0x20) {
		_klog("\npanic(cpu 1, 0x%.16llx): type %i (%s), registers:\n", frame.rip, frame.vector, g_exception_str[frame.vector]);
		_klog("cr0: 0x%.16llx, cr2: 0x%.16llx, cr3: 0x%.16llx, cr4: 0x%.16llx\n", read_cr0(), read_cr2(), read_cr3(), read_cr4());
		_klog("rax: 0x%.16llx, rbx: 0x%.16llx, rcx: 0x%.16llx, rdx: 0x%.16llx\n", frame.rax, frame.rbx, frame.rcx, frame.rdx);
		_klog("rsp: 0x%.16llx, rbp: 0x%.16llx, rsi: 0x%.16llx, rdi: 0x%.16llx\n", frame.rsp, frame.rbp, frame.rsi, frame.rdi);
		_klog("r8:  0x%.16llx, r9:  0x%.16llx, r10: 0x%.16llx, r11: 0x%.16llx\n", frame.r8, frame.r9, frame.r10, frame.r11);
		_klog("r12: 0x%.16llx, r13: 0x%.16llx, r14: 0x%.16llx, r15: 0x%.16llx\n", frame.r12, frame.r13, frame.r14, frame.r15);
		_klog("rfl: 0x%.16llx, rip: 0x%.16llx, cs:  0x%.16llx, ss:  0x%.16llx\n", frame.rflags, frame.rip, frame.cs, frame.ss);
		_klog("fault cr2: 0x%.16llx, error code: 0x%.16llx, fault cpu: 1\n", read_cr2(), frame.err);

		_klog("\nLuxeOS version:\n%s\n", g_luxeos_rel_str);
		_klog("\nKernel version:\n%s (%s/%s)\n", g_kernel_ver_str, g_kernel_configuration_str, g_kernel_arch_str);

		for (;;) {
			__asm__ volatile("hlt");
		}
	} else if (frame.vector >= 0x20 && frame.vector <= 0x2f) {
		if (g_int_handlers[frame.vector] != NULL) {
			g_int_handlers[frame.vector]();
		}
		// eoi
	}
}