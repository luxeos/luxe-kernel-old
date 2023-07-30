/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __SYM_H_
#define __SYM_H_

#include <luxe.h>

typedef struct {
	uintptr_t addr;
	char *name;
} symbol_t;

extern const symbol_t _symtab[];

#endif /* __SYM_H_ */