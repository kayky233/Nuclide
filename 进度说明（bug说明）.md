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

