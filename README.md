# Oray_DDNS
## 编译花生壳C源码做成So动态链接库供android工程使用，实现内网穿透功能
1.  上花生壳官网下载SDK，src文件夹下面就是c源码
2.  新建android工程，在src/main/下面新建名为jni的文件夹，将所有c源码导入进去
3. 在jni文件夹下新建名为Android.mk的文件，百度上搜索也行，套用公共模板改写
4. cmd命令进入到jni文件下，使用`ndk-build `命令编译C代码（确保gradle文件、ndk环境配置正确）
5. 成功则会出现相应的So库

