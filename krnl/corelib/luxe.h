/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __LUXE_H_
#define __LUXE_H_

#include <config.h>
#include <arch.h>

#include <debug/klog.h>

#include <assert.h>
#include <stdarg.h>
#include <stdint.h>

#if defined(CONFIG_X86_64)
#include <luxe/x86_64/luxe_asm.h>
#endif

#include <luxe/luxe_status.h>

#endif /* __LUXE_H_ */