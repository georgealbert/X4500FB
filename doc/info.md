研究这个东西的目的是了解一下硬件，玩玩git

为了我的e6400苦逼的X4500（8086:2A42）能显示正常的native resolution，一直都搞不定，考虑自己写个驱动试试。

## 胡思乱想

* 水果下的是utf-8编码的啊。。。在windows上打开一看乱码，呜呜。

## Framebuffer是干什么的呢?

## 思考

IOKit的架构真是不错。感觉比linux的清晰不少。

* 是不是实现了IOFramebuffer的virtual function 就ok了？<https://developer.apple.com/library/mac/documentation/Kernel/Reference/IOFramebuffer_reference/translated_content/IOFramebuffer.html>

  EDID部分直接写死boot display的算了

* 如何控制硬件的呢？


* 为什么是从显卡获取显示器的EDID信息

  ATI的卡有atirom可以读取，intel的呢？

* IONDR
  
  10.6.8以后AppleIntelGAMX3100FB.kext不再依赖IONDR了。很多hackintash的fb驱动都是直接继承IONDR class，10.6.8后直接over。

  是给power mac用的老代码，居然是直接用 getSymbole("DoDriverIO",...)的方式找到地址，直接填6个参数调用,bt啊，但是在10.6.8的dump中看不见这个字符串，怪了

* vim and ctags

  ctags确实不如xcode看代码给力，按文本grep是无法和按语义分析的ide抗衡的，不过一般情况下ctags也不错了，c++真是个bt的语义，哎.

### DSDT

* dsdt折腾了很久，只有几次在10.6.5和10.6.7下能进系统，那界面确实是漂亮，除了cursor是一个大方框的乱码，但是不知道为什么就算不改dsdt.aml，重启了几次就再也进不去了，不是黑屏就是蓝屏。如果改了X3100.kext，试试3D加速，那是100%的灰屏。

### url

10.6.8的是2.2版本的，[392.1的是IOGraphicsFamliy.kext 2.2的](http://opensource.apple.com/tarballs/IOGraphics/IOGraphics-392.1.tar.gz)

虽然是power版的1999年的，里面有些资料不错，比如piexl的layout，硬件相关的东西[design pci cards on power](https://developer.apple.com/legacy/library/documentation/hardware/DeviceManagers/pci_srvcs/pci_cards_drivers/Designing_PCI_Cards_Drivers.pdf)
