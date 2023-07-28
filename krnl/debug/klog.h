#ifndef __KLOG_H_
#define __KLOG_H_

#define klog(fmt, ...) _klog("%s: " fmt "\n", __func__, ##__VA_ARGS__)

void _klog(char *fmt, ...);

#endif /* __KLOG_H_ */