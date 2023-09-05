/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#include <boot/boot.h>
#include <dd/fb/fb.h>

#include <luxe.h>

fb_info_t g_fb_info;

void fb_init()
{
	if (framebuffer_request.response->framebuffer_count < 1) {
		klog("no framebuffers present!");
		return;
	}

	g_fb_info.addr =
		(uint32_t *)framebuffer_request.response->framebuffers[0]->address;
	g_fb_info.width = framebuffer_request.response->framebuffers[0]->width;
	g_fb_info.height = framebuffer_request.response->framebuffers[0]->height;
	g_fb_info.pitch = framebuffer_request.response->framebuffers[0]->pitch;
	g_fb_info.bpp = framebuffer_request.response->framebuffers[0]->bpp;

	klog(
		"framebuffer addr = 0x%lx, width: %lu, height: %lu, pitch: %lu, bpp: %u",
		g_fb_info.addr, g_fb_info.width, g_fb_info.height, g_fb_info.pitch,
		g_fb_info.bpp);

	klog("done");
}

void putpixel(int x, int y, uint32_t color)
{
	g_fb_info.addr[y * g_fb_info.width + x] = color;
}