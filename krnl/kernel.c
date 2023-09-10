/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <acpi/hpet.h>
#include <proc/scheduler.h>
#include <luxe.h>

__attribute__((noreturn))
void sched_test(uint64_t id)
{
	(void)id;
	while (true) {
		sched_sleep(500);

		klog("this is schedtest");
	}
}

void kernel_init(void)
{
	klog_init();
	arch_init();

	task_t *test = sched_new("sched_test", sched_test, false);
	sched_add(test);

	for (;;) {
		__asm__ volatile("hlt");
	}
}