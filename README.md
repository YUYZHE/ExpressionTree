# 表达式二叉树

## 一、题目表述

​		**使用二叉树来求解表达式输入一个表达式（表达式中的数可以是==多位数==，可以含==多层括号==），利用二叉树来表示该表达式，创建表达式树，然后利用二叉树的遍历操作求表达式的值。**

## 二、分析

### 2.1 解决思路

+ 1、 输入为中缀表达式，直接使用中缀表达式建立二叉树较为麻烦，可将中缀表达式转换为前后缀表达式再进行建树。**本次实验使用后缀表达式建树。**
+ 2、将中缀表达式转为后缀表达式可使用栈。
+ 3、要考虑多位数、浮点数，**本次实验采用每个操作符都为字符串，即将原表达式分为若干子字符串，以分离多位数、浮点数和运算符。**
+ 4、利用栈建立二叉树，并用递归求值。

### 2.2 中缀表达式转为后缀表达式

- 1、中缀表达式即我们常见数学表达式入**1+3*(5-4)/6**，转为后缀表达式更便于计算机识别计算。
- 2、转换过程使用**一个栈**，一个用于存储结果的**后缀表达式数组**。
- 一般过程为：
	- 1）从左到右扫描每个字符
	- 2）针对每个字符有以下操作：
		- i）如果是**'('**直接入栈（操作符栈）
		- ii）如果为**')'**，弹栈，知道遇到'('为止，将元素放入后缀数组
		- iii）**'+'**、**'-'**、**'*'**、**'/'**循环判断若当前元素优先级低则弹栈将其放入后缀表达数组，循环结束意味着当前元素优先级高，则入栈
		- iiii）**数字**直接入后缀数组
		- iiiii）扫描完中缀表达式后，将操作符栈中的**所有操作符弹出并输出到后缀表达式栈**

### 2.3 建树

+ 一个用于建树的栈
+ 遇到**数字**直接入栈，遇到**运算符**则弹出**两个**元素作为运算符的两个**子结点**，然后压栈
+ 最后栈中只剩一个元素，即为最后的表达式树

### 2.4 遍历求值

+ 递归求值（中序）

## 三、具体实现

### 3.1 将字符串分离

+ **由于有多位数、浮点数等，单个字符操作复杂，所以将表达式转为若干子字符串**

+ ~~~c++
	/**
	 * @brief 将数字和运算符分割成子字符串存入vector向量中
	 * @param expreesion 原表达式
	 * @param result 分割后的子字符串向量
	*/
	void ExpressionSplit(string expreesion, vector<string>& result) {
		int i = 0;
		while (expreesion[i] != '\0') {			//循环读取表达式内容
			switch (expreesion[i]) {
			case '(':
			case ')':
			case '+':
			case '-':
			case '*':
			case '/': {							//若为运算符
				string bufstrings;				//临时字符串
				bufstrings += expreesion[i];	//赋给临时字符串
				result.push_back(bufstrings);	//放入字符串向量容器中
				i++;
				break;
			}
			default: {
				string bufstring;
				while ((expreesion[i] >= '0' && expreesion[i] <= '9')
					|| expreesion[i] == '.') {	//若为数字或小数点，循环读取到不是数字或小数点为止
					bufstring += expreesion[i];	//用临时字符串接收
					i++;
				}
				result.push_back(bufstring);	//放入容器
				break;
			}
			}
		}
	}
	~~~

### 3.2 中缀转后缀

+ **将分离好的中缀表达式字符串容器进行后缀转换**

+ ~~~ c++
	/**
	 * @brief 将中缀表达式转为后缀表达式（表达式为已经进行数字运算符分离后的容器）
	 * @param infix 中缀表达式
	 * @param suffix 后缀表达式
	*/
	void ExpressionConversion::InfixToSuffix(vector<string> infix, vector<string>& suffix) {
		for (auto& i_infix : infix) {		//遍历中缀表达式
			switch (i_infix[0]) {			//字符串首元素即可判断是数字还是运算符
			case '(': {						//如果是'('直接入栈（操作符栈）
				Push("(");
				break;
			}
			case ')': {						//如果为')'，弹栈，知道遇到'('为止，将元素放入后缀表达式容器
				string e = Pop();
				while (e[0] != '(') {
					suffix.push_back(e);
					e = Pop();
				}
				break;
			}
			case '+':
			case '-':
			case '*':
			case '/': {
				if (IsEmpty()) {			//栈为空则直接入栈
					Push(i_infix);
					break;
				}
				string e = GetTop();
				while (GetPriority(i_infix[0]) <= GetPriority(e[0])) {	//否则循环判断若当前元素优先级低则弹栈将其放入后缀表达式容器
					suffix.push_back(Pop());
					if (IsEmpty())
						break;
					e = GetTop();			
				}
				Push(i_infix);				//循环结束意味着当前元素优先级高，则入栈
				break;
			}
			default: {						//数字直接入后缀数组
				if (i_infix[0] >= '0' && i_infix[0] <= '9') {
					suffix.push_back(i_infix);
					break;
				}
				break;
			}
			}
		}
		while (!IsEmpty()) {				//扫描完中缀表达式后，将操作符栈中的所有操作符弹出并输出到后缀表达式栈
			suffix.push_back(Pop());
		}
	}
	~~~

+ 在此之中判断了运算符的优先级，具体函数为

+ ~~~ c++
	/**
	 * @brief 返回字符的优先级
	 * @param ch 需要获取优先级的字符
	 * @return 
	*/
	int ExpressionConversion::GetPriority(char ch) {
		switch (ch) {
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		default:
			return -1;
		}
	}
	~~~

### 3.3 建树

+ 使用栈建立二叉树

+ ~~~ C++
	/**
	 * @brief 解析表达式，建立表达式树
	 * @param expression 原表示
	 * @return 表达式树的根节点
	*/
	TreeNode* MathExpressionTree::ParseExpression(string expression) {
		vector<string> inffix;					//分割后子字符串容器
		ExpressionSplit(expression, inffix);	//将原表达式转换为数字运算符分离的子字符串
	
		ExpressionConversion ec;				//用于将中缀表达式转为后缀表达式
		vector<string> suffix;					//后缀表达式子字符串容器
		ec.InfixToSuffix(inffix, suffix);		//转换函数
	
		Stack<TreeNode* > treestack;			//用于进行表达式转为树的栈
		for (auto& i_suffix : suffix) {			//遍历容器
			switch (i_suffix[0]) {				
			case '+':
			case '-':
			case '*':
			case '/': {							//判断首元素即可判断是数字还是运算符
				TreeNode* bufnode = new TreeNode(i_suffix);		//是运算符新建节点
				bufnode->rchild = treestack.Pop();
				bufnode->lchild = treestack.Pop();
				treestack.Push(bufnode);						//操作完后入栈
				break;
			}
			default: {
				if (i_suffix[0] >= '0' && i_suffix[0] <= '9') {	//若是数字
					treestack.Push(new TreeNode(i_suffix));		//直接入栈
					break;
				}
				break;
			}
			}
		}
		return treestack.Pop();
	}
	~~~

### 3.4 遍历求值

+ 即递归求值

+ ~~~ C++
	/**
	 * @brief 表达式遍历求值过程
	 * @param node 传入根节点
	 * @return 计算结果
	*/
	double MathExpressionTree::Evaluate(TreeNode* node) {
		if (node == nullptr)
			return 0.0;
		switch (node->data[0]) {
		case '+':
			return Evaluate(node->lchild) + Evaluate(node->rchild);
		case '-':
			return Evaluate(node->lchild) - Evaluate(node->rchild);
		case '*':
			return Evaluate(node->lchild) * Evaluate(node->rchild);
		case '/':
			return Evaluate(node->lchild) / Evaluate(node->rchild);
		default:
			return stod(node->data);	//将字符串类型转为double类型
		}
	}
	~~~

## 四、结果

+ 编写测试函数

+ ~~~ c++
	//测试函数
	void MathExpressionTreeTest() {
		string str[5];						//定义五个表达式
		str[0] = "1+2*(3.3+4)/20";
		str[1] = "1+2*(5-3)/2";
		str[2] = "12/3+2.5/4-1";
		str[3] = "4.8*2+0.5-3";
		str[4] = "1+2-3*4/5+(6-7)*(8/9)";
		cout << "有以下表达式：" << endl;
		for (int i = 0; i < 5; i++) {
			cout << str[i] << endl;
		}
		cout << endl;
	
		MathExpressionTree met0(str[0]);	//表达式转换到二叉树
		MathExpressionTree met1(str[1]);
		MathExpressionTree met2(str[2]);
		MathExpressionTree met3(str[3]);
		MathExpressionTree met4(str[4]);
		cout << "解析为二叉树后：" << endl;	//转换结果
		cout << str[0] << "\t\t==> " << met0.ToString() << endl;
		cout << str[1] << "\t\t==> " << met1.ToString() << endl;
		cout << str[2] << "\t\t==> " << met2.ToString() << endl;
		cout << str[3] << "\t\t==> " << met3.ToString() << endl;
		cout << str[4] << "\t==> " << met4.ToString() << endl;
		cout << endl;
	
		cout << "计算结果：" << endl;			//最后值
		cout << str[0] << "\t\t= " << met0.GetResult() << endl;
		cout << str[1] << "\t\t= " << met1.GetResult() << endl;
		cout << str[2] << "\t\t= " << met2.GetResult() << endl;
		cout << str[3] << "\t\t= " << met3.GetResult() << endl;
		cout << str[4] << "\t= " << met4.GetResult() << endl;
		
	}
	~~~

+ 在main函数中调用，运行得到结果

+ ~~~ txt
	有以下表达式：
	1+2*(3.3+4)/20
	1+2*(5-3)/2
	12/3+2.5/4-1
	4.8*2+0.5-3
	1+2-3*4/5+(6-7)*(8/9)
	
	解析为二叉树后：
	1+2*(3.3+4)/20          ==> +(1,/(*(2,+(3.3,4)),20))
	1+2*(5-3)/2             ==> +(1,/(*(2,-(5,3)),2))
	12/3+2.5/4-1            ==> -(+(/(12,3),/(2.5,4)),1)
	4.8*2+0.5-3             ==> -(+(*(4.8,2),0.5),3)
	1+2-3*4/5+(6-7)*(8/9)   ==> +(-(+(1,2),/(*(3,4),5)),*(-(6,7),/(8,9)))
	
	计算结果：
	1+2*(3.3+4)/20          = 1.73
	1+2*(5-3)/2             = 3
	12/3+2.5/4-1            = 3.625
	4.8*2+0.5-3             = 7.1
	1+2-3*4/5+(6-7)*(8/9)   = -0.288889
	~~~

	- 经验证，结果正确。

## 五、最后

通过这次实验，更加熟悉了栈的应用，二叉树的应用，在编写过程中也查阅过很多资料……