# pragma once

#include<vector>
#include "vihicle.h"
#include "utility.h"
//以轮次为单位进行匹配

/*匹配策略一：(更改！）
1.满足更多人的订单需求（优先顺风车）
2.车辆匹配距离最近的人
步骤：
1.就经过站点数由大到小排列
2.一辆辆车寻找离车最近的且途径站点最多的订单a（若没有合适站点则循环直至找到最近站点or该轮全部订单结束）
3.由a做匹配项，寻找有无a的子集（终止条件是：1.满4个订单 2.该轮乘客匹配完）
*/

/*匹配策略二：
1.一车接一单
2.贪心匹配最接近的订单
(每车接每人的总距离最短）

衡量标准：
接的总单数更多
如果相同，选二*/

class Allocation {
public:
	//std::vector<int> matching();//匹配用户和车
	void Str_One();//返回匹配策略一接单数
	void Str_Two();//返回策略二的接单数
	void Str_Outcome();//返回并输出结果
private:

}SL_Allocation;