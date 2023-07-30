/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <cpu/cpu.h>
#include <debug/sym.h>

#include <luxe.h>

void backtrace(uint8_t walk_max)
{
	(void)walk_max;
	uint64_t *base;
	__asm__ volatile("mov %%rbp, %0" : "=g"(base) :: "memory");

	for (int i = 0;; i++) {
		base = (uint64_t *)*base;
		uint64_t return_addr = *(base + 1);
		
		if (return_addr == (uint64_t)NULL || base == NULL || return_addr < (uint64_t)0xffffffff80000000) {
			break;
		}

		int idx = _sym_get_index(return_addr);
		if (idx < 0) {
			_klog("    [%.16lx]  <\?\?\?>\n", return_addr);
		} else {
			_klog("    [%.16lx]  <%s+0x%04x>\n", return_addr, _symtab[idx].name, return_addr - _symtab[idx].addr);
		}
	}

	_klog("End of trace.\n");
}

int _sym_get_index(uint64_t addr)
{
	for (int i = 0; _symtab[i].addr < UINTPTR_MAX; i++) {
		if (_symtab[i].addr < addr && _symtab[i+1].addr >= addr) {
			return i;
		}
	}

	return -255;
}