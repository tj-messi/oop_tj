·直接用Update3替换掉大作业文件夹
common：公共文件
	注意：class_aat.cpp - 部分给出，需要自行补充完整
	·需自行补充完整的部分为超级大类的一堆构造函数及析构函数，以及末尾的三个函数，最主要的工作量在过程分析函数和参数打印函数上（两个函数加起来有将近四百行）
	·判断IP地址是否合法的函数需要再搬一次（即使在my_ping里面已经被声明过static了）
	·已经给出来了将IP地址从字符串类型转化为整型的函数（需要实现的倒数第三个函数），建议至少再增加一个从整型到字符串类型的函数（主要他这个IP地址用unsigned int存的，跟字符串来回互转很烦）

include：公共头文件
	注意：class_aat.h - 部分给出，需要自行补充完整
	·没太看出来需要自行补充完整的部分是什么，应该都是些有需求就可以自行添加的，尤其是可以加static成员函数，有需要就加
              lib_aat_tools.h - 不准改动

lib：公共库文件
	注意：lib_common_tools.lib已给出，需要打开 class_aat.h 中的 ENABLE_LIB_COMMON_TOOLS 才能用
              lib_common_tools.pdb不要改动，仅为了去除编译警告

test_args_analyse_tools：class_aat工具集测试函数
	注意：test_args_analyses_tools.cpp - 已完整给出，建议的命令行测试在.cpp最后的注释中
	·除了测试需要改条件编译选项之外，代码很完整不需要改动，可以拿这个来测试工具集写得对不对

my_ping：ping工具参数模拟程序
	注意：my_ping.cpp - 有一个条件编译选项需要置0/1后分别测试，有一个函数需要实现
	·有一个条件编译选项IPADDR_IS_FIXED_ARGS，分别表示IP地址为固定参数或者可变参数，两种需要分别测试一下
	·只需自行实现is_isaddr_valid函数，即判断IP地址是否合法，14-b4中已写过，基本上直接copy过来就行
	·有一个参数分析函数，在class_aat.cpp里面实现过，不重复统计
	·pdf里面说参数分析部分必须使用工具集，不能简单改小作业，没太看出来是什么意思，我寻思分析参数的函数不是在工具集里面写的吗，这也没法改小作业啊，而且这个main函数也不是我写的啊

my_convert：Windows和Linux格式的文本文件互转工具
	注意：my_convert.cpp - 有一个条件编译选项需要置0/1后分别测试，其他不需要改动
	·有一个条件编译选项SRC_DST_IS_FIXED_ARGS，分别表示转换前后的文件名是固定参数或者可变参数，两种需要分别测试一下
	·参数分析函数在class_aat.cpp里面实现过，不重复统计
	·除了测试需要改条件编译选项之外，代码很完整不需要改动，命令的实际实现部分也不需要搬过来
	·pdf里面说参数分析部分必须使用工具集，同上
·合计八个构造函数，一个析构函数，一个把IP地址从字符串转成整数的函数，一个参数分析函数，一个打印参数函数，两个判断IP地址是否合法的函数（实际是一个），以及若干自行添加的部分