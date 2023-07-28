/**
 * LuxeOS (c) 2023 by Jozef Nagy
 *
 * LuxeOS is licensed under a
 * Creative Commons Attribution-NoDerivatives 4.0 International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nd/4.0/>.
 */

#ifndef __KLOG_H_
#define __KLOG_H_

#define klog(fmt, ...) _klog("%s: " fmt "\n", __func__, ##__VA_ARGS__)

void _klog(char *fmt, ...);

#endif /* __KLOG_H_ */