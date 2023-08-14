# 数据库练习 DDL 数据库定义语言相关

有一个商店的数据, 记录客户及购物情况, 有以下三个表组成:

1. 商品`goods`(商品编号`goods_id`, 商品名`goods_name`, `单价unitprice`, 商品类别`category`, 供应商`provider`)
2. 客户`customer`(客户号`customer_id`, 姓名`name`, 住址`address`, 邮箱`email`, 性别`sex`, 身份证`card_id`)
3. 购买`purchase`(购买订单号`order_id`, 客户号`customer_id`, 商品号`goods_id`, 购买数量`nums`)

要求：

1. 每个表明确的主外键
2. 客户的姓名不能为空值
3. 邮箱不能重复, 身份证号不能重复
4. 客户的性别(男, 女)
5. 其他要求自行根据实际情况分析
