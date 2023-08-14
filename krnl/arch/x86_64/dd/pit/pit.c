/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/pit/pit.h>

#include <luxe.h>

static uint64_t g_pit_ticks = 0;

void pit_tick()
{
	g_pit_ticks++;
}