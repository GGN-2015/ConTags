# ConTags

ConTags 是一种数据标记语言，它可以用于表示任何树形数据结构信息。ConTags 为我们提供了一种既能保持数据自解释性，又不使用转义字符的方式对数据进行分层。

## 为什么要用 ConTags

数据的意义必然位于数据之外。简而言之，对于一段存储在计算机中的二进制数据，倘若没有一个独立于这个数据之外的系统去对他加以“解释”，那么这个数据本身并无意义。我们在 C 语言中经常使用一种名为“转移字符”的技术来描述字符串中的特殊字符，例如在字符串 `"Hello World\n"` 中 `\n` 表示换行符。这里的字符 `\n` 需要经过编译程序的“解释”才能够得到真正被存储在计算机内存中的数据。

这种转义为我们带来了一种难以忽视的麻烦。当我们使用双引号来作为数据的“包络”时，我们就无法直接在数据部分中使用双引号这个字符本身。为了保证数据表达的完备性，我们不得不对包络内的数据中加入“转移项”，通常为以 `\` 开头的一串字符，他们的出现用于表示某个在包络中原本难以表示的字符——但这种表示是十分“不自然”的，这导致我们难以使用简单的内存空间映射来获取实际的数据，而必须在使用时对数据进行扫描转义。笔者认为，当我们不得不使用“外部”的规则来左右“内部”的数据时，“外部”和“内部”之间存在一种我们所不期待的耦合。

### ConTags 的理念

ConTags 旨在将原本需要在使用数据时进行的扫描转义过程省略，转而将相应的处理过程在数据生成时完成。换言之，我们将在数据生成时选择一个更为合适的“包络”以保证内部的数据可以被简单的提取并直观地被解释，而不需要使用任何转义字符。这种设计在理论上是同样是高效且可行的，而且也可以用来为我们提供一套可靠的自解释数据编码方式。在 OSI/RM 应用层常用的数据表示方式中，我们可以看到，大多数的数据表示中都会定义一些特殊的“包络”字符或者“包络”格式。这些“包络”字符或者“包络”格式，在“被包络”的部分是不允许出现的，在某些场合中这种规定并不会引发太多的问题，但是在某些场合中却时常导致潜在的不直观性与危险性。以 SQL 注入为例，当我们试图将一个字符串变量填充到 SQL 语句中并进行相应的查询时，由于包络的限制，导致我们不得不对我们的原始数据进行“逆转义”以保证我们查询的正确性，否则我们的数据库将可能受到恶意的攻击。

对于常见包络符的一些问题总结如下：当我们使用双引号作为包络符时，我们假设数据中不含双引号，且数据中不包含嵌套的子数据。当我们使用一对括号来作为包络符时，我们假设数据中可以包含嵌套的子数据，但是数据部分中不能以括号本身作为数据。我们将这些问题称为“包络约束”，即采用某种包络符时，“外层”对“内层”在表述上的限制。ConTags 在理念上希望一方面兼容对数据传输的要求，另一方面又能保留一定的自解释性。

### ConTags 的优势

当我们使用一种不含转义字符的包络方式对数据进行包络时，我们可以认为解包后的数据一定是带包络数据中的一个字串。这也就意味着我们不需要在内存中重新申请一段存储空间以储存这个数据解包之后的部分，只需要存储一个指向带包络数据中某位置的指针以及一个有效区域的长度就可以实现这一算法——在本文中这种技术被称为“子串视图”技术。在保证原字符串不被修改时，字串视图可以访问到原字符串的某个字串的一个只读备份。由于包络本身的代价相比于数据部分而言一般不大，因此这种对拷贝操作的避免往往会带来显著的时间空间收益。

## ConTags 的实现

ConTags 技术规定了无限多种“包络符”，原则上我们可以使用其中的任意一种作为我们使用的包络符号，只要我们能够保证在数据部分中没有出现过这种包络符号的“包络结束符”。ConTags的“包络起始符”由三部分组成：“括号部分”、“解释部分”、“分隔部分”。一个常见的 ConTags “包络起始符”形如：`"<<<String|"`，其中 `"<<<"` 是这个包络起始符的括号部分，`"String"` 是解释部分，`"|"` 是分隔部分。与这个“包络起始符”相对的包络终止符一定具有这样的形式：`"|String>>>"`，它与“包络起始符”具有相同的分隔部分与解释部分，括号部分能够恰好相互匹配。由于任何形式化的表述方式都至少基于一种默认的“包络约束”，这种包络约束要么必须使用转义字符以实现表达的完备性，要么直接牺牲了表达的完备性。尽管我们可以以巴克斯-诺尔范式给出 ConTags 包络符的抽象形式，但是我们仍然要使用自然语言，以保证我们不带有那些对包络约束的默认假设。除非特殊说明，下文中提到的所有字符均为 ASCII 码字符，我们假设数据以字节流的形式存在。

ConTags 包络符的括号部分可以包含小括号 `()`，中括号 `[]`，大括号 `{}`，尖括号 `<>` 四种不同括号，这四种括号可以按照任意顺序排列，可以重复任意多次，但**括号部分不能为空**。换言之，ConTags 包络符的括号部分至少要包含一个字符。对于包络起始符而言，它的括号部分可以包含四种**左括号**；而对于包络终止符而言，它的括号部分可以包含四种**右括号**。

ConTags 的解释部分可以包含小写字母，大写字母，数字，下划线 `"_"`与连字符 `"-"` 等 64 种字符，**解释部分可以为空**。解释部分为空的包络称为**匿名包络**，解释部分不为空的称为**命名包络**，非空的解释部分称为“包络名”。一对包络起始符与包络终止符在解释部分具有完全相同的内容，且大小写敏感。ConTags 包络符的解释部分一般用于解释说明被包络部分的含义，也可以使用一串随机字符来缩减包络符的总长度，称为 **随机命名包络**。

ConTags 的分隔部分可以包含井号 `"#"`，竖线 `"|"`，美元符号 `"$"`，AT号 `"@"`，百分号 `"%"`，上尖号 `"^"`，And 符号 `"&"`，感叹号 `"!"`，星号 `"*" 等共九种符号`。ConTags 的**分隔部分有且仅有一个字符**，解释部分的字符集和分隔部分的字符集没有交集。

## ConTags 的示例

以 C 语言中字符串 Hello World 为例，一种可以使用的包络方式如下：

```
<$Hello World
$>
```

在这个例子中，我们不需要使用转义字符就可以将换行符包含于其中（其实这并没有什么好炫耀的，因为转义字符 `\n` 并不是来自双引号的包络约束，而是来自于“相匹配的两个双引号必须要在同一行”这一约束）。

## ConTags 生成算法

给定一段数据，要求我们生成对于该数据的 ConTags 包络数据。我们可以使用以下的算法去生成一个“匿名 ConTags 包络”、“命名 ConTags 包络”、“随机命名 ConTags 包络”、“混合随机命名 ConTags 包络”。只要符合 ConTags 对字符集合的要求，就是合法的 ConTags 包络符，我们示例性地提出了以下几种包络算法。

### 生成匿名 ConTags 包络

```
alpha = 0.5

def FitLen_A(n):
	return (log(n) - log(9) - log(alpha))/log(4) + 1

if 数据中不含美元符号字符'$' 或者 数据中不含右尖括号 '>':
	return <$ 数据内容 $>
else:
	N = max{ceil(FitLen_A(数据部分长度) * 0.5), 2};
	while True:
		for i in range(0, 2):
            生成一对长度为 N 的随机匿名包络 (Left, Right)
            if 数据中不含 包络右部 Right:
                return Left 数据内容 Right
        N = N + 1
```

我们能够证明，这种算法生成出的匿名包络，即使是在被攻击的情况下也不会很长。在此我们可以简述 FitLen\_A 的计算原理：倘若攻击者想要构造一个字符串使得我们的算法迟迟不能给出一个合法的包装，那么他一定会采用这样的一种策略：指定一个常数 $k$，生成一个包含所有长度为 $k$ 的匿名右包络符的字符串，我们可以计算得到这个字符串的长度为 $n=k\times 4^{k-1}\times 9$ 。 $\ln n=\ln k + (k-1)\ln 4 + \ln 9$，假设 $k\geq 3$，我们可以得到 $(k-1)\ln 4 + \ln 9 \leq\ln n$，解得 $k\leq \frac{\ln n - \ln 9}{\ln 4}+1$，当 $k$ 足够大时，表达式近似取等号即 $k\sim \log_4n$。

对于一个攻击者而言，它已经了解到我们采用了一些基于概率的算法，对于攻击者而言，如果他能保证对于某个 $k$，当我们生成一个长度小于等于 $k$ 的数据时，总有不低于 $50\%$ 的概率发生冲突，那么他可以在概率上更好地优化自己的攻击效果。我们令 $\alpha=0.5$，攻击者从所有长度为 $k$ 的右包络中选出一半的包络构成数据串。因此我们计算得到字符串的长度为 $n=k\times 4^{k-1}\times 9\times \alpha$。在这个表达式中通过 $n$ 值估算 $k$ 值就得到了上文中的 $FitLen\_A$ 函数。

我们能够证明，在一般情况下，生成一个有效匿名包络的时间复杂度为 $O(n\log_4 n)$，其中 $n$ 为字符串的长度 。上文中的 `if` 特判是必要的，因为当数据部分为空时，$FitLen\_A$ 函数可能会因为计算 $\log(0)$ 而出错。

### 生成命名 ConTags 包络

```
NAME = 我们给定的包络名
LEN = 我们给定的包络名长度

if 数据中不含 '$' 或者 数据中不含 '>' 或者 数据中不含我们给定的包络名:
	return <包络名$ 数据内容 $包络名>
else:
	根据上文算法生成一个匿名 ConTags 包络 (Left, Right)
	return Left(包络名) 数据内容 Right(包络名)
```

`if` 语句中的判断条件只是 `'$包络名>'` 可以做右包络的一个充分条件，而充要条件是数据中不包含 `'$包络名>' 这个字符串本身。`但是我们建议采用这种判断方式，以保证不会产生人眼观察时的混淆。

### 生成随机命名 ConTags 包络

随机命名 ConTags 包络的主要唯一性保证来自他的随机部分。

```
alpha = 0.5

def FitLen_B(N):
	return (log(N) - log(alpha)) / log(62)

if 数据中不含 '$' 或 数据中不含 '-' 或 数据中不含 '>':
	A = 生成一个随机的小写字母、大写字母或者数字
	return <-A$ 数据内容 $A->
else:
	N = max(ceil(FitLen_B(数据长度) * 0.5), 2)
	A = 随机生成一个长度为 N 的小写字母、大写字母或者数字构成的字符串
	while A 在数据部分出现过:
		在 A 的尾部随机追加一个 小写字母、大写字母或者数字字符
	return <-A$ 数据内容 $A->
		
```

假如攻击者想要攻击我们的算法，他会选定一个长度 $k$，然后尽可能地枚举所有长度为 $k$ 的随机字母数字串。假如攻击者列举了 $\alpha=50\%$ 的所有长度为 $k$ 的随机串，那么他的字符串长度 $n=k\times 62^k\times \alpha$。根据与生成匿名 ConTags 包络中类似的放缩方式，我们可以得到 $k\leq \frac{\ln n-\ln \alpha}{\ln 62}$。使用后缀数据结构实现该算法可以将时间复杂度控制在 $O(n + \log_{62} n)$左右。

### 生成混合随机命名的 ConTags 包络

混合随机命名的 ConTags 包络的包络名一部分由用户给出，另一部分由算法随机生成，其中用户给出的部分只允许包含字母数字下划线，不允许包含连字符 `'-'`。尽管算法上能够实现，我们不建议用户指定很长的包络名。

```
if 指定包络名 not in 数据:
	return <指定包络名$ 数据内容 $指定包络名>
else:
	根据随机命名 ConTags 算法生成一个随机串 A
	return <指定包络名-A$ 数据内容 $指定包络名-A>
```

在生成的包络名中，连字符之后内容为随机生成的包络名，连字符之前的部分为指定的非随机生成的包络名。

## 默认的 ConTags 嵌套协议

上文中所描述的 ConTags 包络只能实现对某一数据的包络，但却难以实现对于整个树形结构数据的表示。换言之，上述给出的算法主要用于生成对叶子结点上数据的包络，但是我们仍未给出对于非叶子节点如何进行包络表示。ConTags 的原理并不包含这一协议，因此每个使用 ConTags 的人可以根据自己的需要开发一套 ConTags 嵌套协议。我们在这里给出一个默认的 ConTags 嵌套协议以作为示范，当 ConTags 包络使用者没有指明自己所使用的协议时，我们默认他使用我们给出的默认协议。

### 非叶子结点的 ConTags 包络

非叶子结点的 ConTags 包络名必须使用下划线开头，叶子结点的 ConTags 包络名不得以下划线开头，我们以这种方式区分叶子节点和非叶子结点。在非叶子节点的中，我们允许使用空格，制表符，回车符，换行符占位，非叶子节点中的上述四种字符会被忽略。

```
<_UserInfo$
	<UserName$Bob$UserName>
	<UserId$12345$UserId>
$_UserInfo>
```

该示例对应如下树形结构：

```
UserInfo
- UserName : Bob
- UserId   : 12345
```

为了方便人理解阅读这种文本，我们在子包络前使用了空格作为缩进，并在合适的地方进行了换行。但在数据传输中，我们并不需要这种用于排版的字符，有时也可以对传输数据的名字进行适当的缩略甚至匿名以减小传输数据的量。

### 对叶子节点 ConTags 包络进行随机拓展

当数据部分中包含了包络名时，我们必须使用“混合随机命名 ConTags 包络”的生成算法对包络名进行拓展，例如：

```
<_UserInfo$
	<Raw-4d$Raw$Raw-4d>
	<Flat-c5$Flat$Flat-c5s>
$_UserInfo>
```

该示例对应如下的树形结构：

```
UserInfo
- Raw  : Raw
- Flat : Flat
```

换言之，混合随机命名 ConTags 包络中，随机生成的部分不会被当作字段名的一部分。例如示例中出现的 `-4d` 与 `-c5` 就是这样的随机拓展，根据上文中随机命名 ConTags 包络算法可知，这个随即拓展中至少包含两个随机生成的字母或者数字字符。

### 默认协议解析算法

默认协议解析算法采用递归解析的方式进行解析，使用者可以根据自己的使用场景设计基于栈的匹配解析算法，但基于栈的解析算法往往会假设我们使用的协议带有某种对包络的预设限制。例如，当我们使用括号序列来描述一个树形结构时，字符串`{{}{{}}}`可以用来表示一个含四个结点的有根树，在使用栈算法时，我们带有一种这样的预设：后出现的左括号一定先于先出现的左括号得到匹配——而这不符合 ConTags 的设计初衷。

```
def Interprete(lis, 字符串):
	跳过字符串开头的空格、制表符、回车、换行
	if 字符串为空:
		return None
	else:
		while 字符串 非空:
            识别一个合法的左包络，如果无法识别得到合法的左包络，抛出异常
            根据得到的左包络计算对应的右包络，找到右包络下一次出现的位置，找不到抛出异常
            if 左包络是非叶子结点包络:
            	nlis = []
            	对左包络和右包络之间的部分递归调用 Interprete(nlis, 字符串) 算法
            	rt = 新节点
            	rt.根据左包络设置结点名称
            	rt.sons = nlis
            	lis.append(rt)
            else:
            	rt = 新节点
            	rt.根据左包络设置结点名称
            	rt.设置数据部分为左右包络之间的数据
            
            跳过字符串开头的空格、制表符、回车、换行

def Get(整个字符串):
    nlis = []
    Interprete(nlis, 整个字符串)
    return nlis
```

使用 Get 算法最终可以得到一个结点序列，这个节点序列表示我们要接收的数据森林。

## 使用 ConTags 包络二进制数据

当我们设计了一个基于二进制数据的应用层通信协议时，我们往往希望最小化我们传输数据的总量——否则我们可以采用类似 `json` 或者 `html` 等以文本为主的自解释文件格式。因此在对二进制数据进行包络时，我们希望空间上的额外开销应该尽可能少，因此我们应尽可能使用匿名包络或者随机命名包络。上文中给出的几种算法并不能充分利用 ConTags 在空间开销上的优势，这要求使用者根据具体的包络数据额外设计新的包络选择算法。

例如，当我们需要对一个 8 字节（64位）双精度浮点数进行包络时，我们发现，这 8 字节数据中，很难导致右包络冲突。由于我们总共有 36 种长度为 2 的右包络，因此，当我们试图给一个长度小于 72 字节的数据制作包络时，我们可以断言我们只需要使用长度为 2 的包络就一定能够保证右包络不存在于数据部分之中。

而对于一段较长的二进制数据，我们可以讲该数据按照每 72 字节一组进行分段，并对每一段分别进行包络，那么带来的平均数据冗余量为 $\frac{4}{72 + 4}\approx 5.26\%$。对于不太严格的场合，我们可以延长单个分段的长度，并使用随机化的方法确定最终使用的包络符；对于比较严格的场合，我们可以每 64 个字节分一段，并严格筛选可用的包络符。
