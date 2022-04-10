/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
有效字符串需满足：
 左括号必须用相同类型的右括号闭合。
 左括号必须以正确的顺序闭合。
示例 1：

输入：s = "()"
输出：true

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

typedef char StDateType;

typedef struct Stack
{
	StDateType *data;
	int top;				// 栈顶位置
	int capacity;			// 栈的容量
}Stack;

// 栈的初始化
void StackInit(Stack* pSt)
{
	assert(pSt);

	pSt->data = NULL;
	pSt->top = 0;			// 栈顶初始位置定义 (top = -1, 先++后赋值; top = 0, 先赋值后++)
	pSt->capacity = 0;
}
// 栈的销毁
void StackDestroy(Stack* pSt)
{
	assert(pSt);

	free(pSt->data);
	pSt->data = NULL;
	pSt->top = pSt->capacity = 0;
}
// 压栈
void StackPush(Stack* pSt, StDateType x)
{
	assert(pSt);

	if (pSt->top == pSt->capacity)
	{
		int newCapacity = pSt->capacity == 0 ? 4 : pSt->capacity * 2;
		StDateType* tmp = (StDateType*)realloc(pSt->data, newCapacity * sizeof(StDateType));
		if (tmp == NULL)
		{
			printf("realloc failed\n");
			exit(-1);
		}
		else
			pSt->data = tmp;

		pSt->capacity = newCapacity;
	}

	pSt->data[pSt->top++] = x;
}
// 出栈
void StackPop(Stack* pSt)
{
	assert(pSt);
	assert(pSt->top > 0);

	--pSt->top;
}
// 判空
bool StackEmpty(Stack* pSt)
{
	assert(pSt);

	return pSt->top == 0;			// top 等于 0 栈为空，返回 true; 不等于 0 ，返回 false
}
// 栈顶数据
StDateType StackTop(Stack* pSt)
{
	assert(pSt);

	return pSt->data[pSt->top - 1];
}

bool isValid(char * s)
{// 思路：遍历字符串，遇到右括号"( { [", 入栈
//                  遇到左括号") } ]", 与栈顶元素匹配
//                  匹配成功则栈顶元素出栈，继续遍历
//                  匹配失败则直接返回 false
    Stack chars;
    StackInit(&chars);
    while(*s != '\0')
    {
        if(*s == '(' || *s == '{' || *s == '[')
        {
            StackPush(&chars, *s);
        }
        else
        {
            if(StackEmpty(&chars))
            {
                StackDestroy(&chars);
                return false;
            }
            char Top = StackTop(&chars);
            if( (*s == ')' && Top == '(') ||
                (*s == '}' && Top == '{') ||
                (*s == ']' && Top == '['))
            {
                StackPop(&chars);
            }
            else
            {
                StackDestroy(&chars);
                return false;
            }
        }
        s++;
    }


    if(StackEmpty(&chars))
    {
        StackDestroy(&chars);
        return true;
    }
    else
    {
        StackDestroy(&chars);
        return false;
    }
}