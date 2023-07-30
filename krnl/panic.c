/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <dd/uart/uart.h>
#include <cpu/cpu.h>
#include <panic.h>
#include <luxe.h>

__attribute__((noreturn))
void _panic()
{
	wizard_show();
	for (;;);
}

void wizard_show()
{
	_klog("                         /\\\n");
	_klog("                        /  \\\n");
	_klog("                       |    |\n");
	_klog("                     --:'''':--\n");
	_klog("                       :'_' :\n");
	_klog("                       _:"":\\___\n");
	_klog("        ' '      ____.' :::     '._\n");
	_klog("       . *=====<<=)           \\    :\n");
	_klog("        .  '      '-'-'\\_      /'._.'\n");
	_klog("                         \\====:_ ""\n");
	_klog("                        .'     \\\\\n");
	_klog("                       :       :\n");
	_klog("                      /   :    \\\n");
	_klog("                     :   .      '.\n");
	_klog("                     :  : :      :\n");
	_klog("                     :__:-:__.;--'\n");
	_klog("                     '-'   '-'\n");
	_klog("    You have been visited by the mighty wizard.\n");
	_klog("  A fatal error occured, and the computer cannot function properly anymore.\n");
	_klog("  Please send the following to the developers:\n\n");
}