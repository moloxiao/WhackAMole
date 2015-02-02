package com.poxiao.pay.whackamole;

public enum PAY {

	PayGold1(1, "新手礼包", 1000, "付费10元即可永久免费游戏，赠送10点体力！"), 
	PayGold2(2, "体力值礼包", 1000, "付费10元即可获得10点体力，点击确定获得！"),
	PayGold3(3, "挑灯夜战礼包", 1000, "付费10元即可获得10次挑灯夜战机会，点击确定获得！"),
	PayGold4(4, "混合礼包", 1000, "付费10元即可获得5点体力、5次挑灯夜战机会，点击确定获得！"),
	PayGold5(5, "挑灯夜战免费礼包", 0, "你还有n次挑灯夜战机会，点击确定立即挑灯夜战，消灭更多地鼠！");

	// 成员变量
	private int type;
	private String desc;
	private int money;
	private String name;

	// 构造方法
	private PAY(int type, String name, int money, String desc) {
		this.type = type;
		this.name = name;
		this.money = money;
		this.desc = desc;
	}

	// 普通方法
	public static String getName(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.name;
			}
		}
		return null;
	}

	public static int getMoney(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.money;
			}
		}
		return 0;
	}

	public static String getDesc(int type) {
		for (PAY c : PAY.values()) {
			if (c.getType() == type) {
				return c.desc;
			}
		}
		return null;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public int getMoney() {
		return money;
	}

	public void setMoney(int money) {
		this.money = money;
	}

}
