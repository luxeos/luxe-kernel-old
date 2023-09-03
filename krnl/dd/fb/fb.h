/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __FB_H_
#define __FB_H_

#include <luxe.h>

typedef struct {
	uint32_t *addr;
	uint64_t width;
	uint64_t height;
	uint64_t pitch;
	uint16_t bpp;
} fb_info_t;

extern fb_info_t g_fb_info;

void fb_init();
void putpixel(int x, int y, uint32_t color);

#endif /* __FB_H_ */