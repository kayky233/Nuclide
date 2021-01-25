# 1.21日

## geant4 部分：

目前已完成：1. 物理模型调试完毕，可以用（指已经不报错了）；

​                      2. physicslists 选用了FTFP_BERT，已跑通。

​                      

目前问题：ui命令not found 的错误。

该行代码位于 vis.mac 文件中，同样的命令在其他example中能正常运行，但是不知道为什么在这里会有COMMAND NOT FOUND 的错误，原因还在寻找中。

```c++
# Use this open statement to create an OpenGL view:
/vis/open OGLIX 600x600-0+0
***** COMMAND NOT FOUND </vis/open OGLIX 600x600-0+0> *****

***** Batch is interrupted!! *****

```

# 1.22日

ui解决，.mac文件的注释要用 # 而不是 // 导致command not found 的问题解决，目前好像就只需要解决pyhsicslists的问题了，用封装好的phys可以生成 .root,但是无法解决demo里定义的时间的问题。

# 1.25日

rdecay01 项目完成能谱绘制工作，不过目前还有一个问题是多源能谱的绘制以及能谱的展宽，以及模拟出的能谱几乎都一样的问题。