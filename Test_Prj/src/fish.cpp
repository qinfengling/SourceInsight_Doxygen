/**
 * @file				fish.cpp
 * @brief			该文件用于描述生成Fish的过程。
 * @author			Mikeqin
 * @date			2013年1月12日星期六
 * @version			初稿
 * @par				版权所有 (C), 2013-2023, 天道酬勤
 * @par History:
 * 1.日    期: 		2013年1月12日星期六
 *   作    者: 		Mikeqin
 *   修改内容:	创建文件
 *
 * 2.日    期: 		2013年1月12日星期六
 *   作    者: 		Mikeqin
 *   修改内容:	增加各模块的注释
*/
#include "fish.h"
#include "ApplyHint.h"
#include "ApplyHouseHint.h"
#include "input.h"
#define SHOW	1	

/**
 * @brief eAttr注释   
*/
enum eAttr {
	NATION, 	
	COLOR, 	
	PET,		
	BEVERAGE,	
	CIGARETTE,	
	HOUSE,	
};

/**
 * @brief	TESTSTRU的注释
*/
typedef struct TESTSTRU
{
	int var1;
	int var2;
}

#ifdef SHOW
static int g_hint_cnt = 0;///<此处的注释为手写，以后机会再添加。
static bool g_only_size = true;
int g_test_var = 0;
#endif

/**
 *@brief: 		apply_hint
 *@details:		apply_hint注释
 *@param[in]	const CSolutionSet &in_set  
 				CSolutionSet &out_set       
 				CApplyHint *apply_hint      
 				const CHint *hints          
 				int num                     
 *@param[out]	无
 *@retval:		static
 */
static void apply_hint(const CSolutionSet &in_set, CSolutionSet &out_set, CApplyHint *apply_hint,
					   const CHint *hints, int num)
{
	CSolutionSet set;

	set = in_set;
	for (int i=0; i<num; i++) {
		apply_hint->SetHint(hints[i]);
		out_set.RemoveAll();
		apply_hint->Apply(set, out_set);
#ifdef SHOW
		printf("\n\n澧炲姞绾︽潫: %s\n",HINTS_STR[g_hint_cnt++]);
		if (out_set.GetSize()<=4) {
			out_set.Show();
		}
		else {
			out_set.Show(g_only_size);
			if (g_only_size) {
				printf("...\n");
			}
		}
#endif
		set = out_set;
	}
}

static void apply_self_hint(const CSolutionSet &in_set, CSolutionSet &out_set)
{
	CApplyHint hint;
	apply_hint(in_set, out_set, &hint, SELF_HINT, SELF_HINT_CNT);
}

static void apply_ordered_neighbor_hint(const CSolutionSet &in_set, CSolutionSet &out_set)
{
	CApplyOrderedNeighborHint hint;
	apply_hint(in_set, out_set, &hint, ORDER_NEIGHBOR_HINT, ORDER_NEIGHBOR_HINT_CNT);
}

static void apply_neighbor_hint(const CSolutionSet &in_set, CSolutionSet &out_set)
{
	CApplyNeighborHint hint;
	apply_hint(in_set, out_set, &hint, NEIGHBOR_HINT, NEIGHBOR_HINT_CNT);
}

/**
 *@brief: 		find_solution
 *@details:		该函数是功能的入口。
 *@param[in]	CString &buf  
 *@param[out]	无
 *@retval:		
 */
int find_solution(CString &buf)
{
	CSolutionSet set, new_set;
	CSolution sln;
	int i;

	for (i=0; i<MAGIC_NUM; i++) {
		sln.Init(INIT_HINT[i]);
	}
	set.Add(sln);
#ifdef SHOW
	printf("鍒濆鐘舵�乗n");
	set.Show();
#endif

	apply_self_hint(set, new_set);

	set = new_set;
	apply_ordered_neighbor_hint(set, new_set);

	set = new_set;
	apply_neighbor_hint(set, new_set);

#ifdef SHOW
	printf("\n鎺ㄧ悊缁撴潫銆俓n");
#else
	new_set.Show(buf);
#endif
	return new_set.GetSize();
}



