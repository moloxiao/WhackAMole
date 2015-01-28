package com.poxiao.pay.whackamole;

import com.tallbigup.buffett.OrderInfo;

public class WhackAMolePayInfo {

	private static WhackAMolePayInfo instance;
	
	private WhackAMolePayInfo(){
	}
	
	public static WhackAMolePayInfo getInstance(){
		if(instance == null){
			instance = new WhackAMolePayInfo();
		}
		return instance;
	}
	
	public OrderInfo getOrderInfo(int payCode, String sequence, String orderId) {
		OrderInfo orderInfo = new OrderInfo();
		orderInfo.setPrice(PAY.getMoney(payCode));
		orderInfo.setProductName(PAY.getName(payCode));
		orderInfo.setOrderDesc(PAY.getDesc(payCode));
		orderInfo.setOrderId(orderId);
		orderInfo.setPayPointNum(payCode);
		orderInfo.setSequence(sequence);
		return orderInfo;
	}
}
