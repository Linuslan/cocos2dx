/****************************************************************************
Copyright (c) 2015-2017 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.ty.ctr.ex.BaseResponse;
import com.ty.ctr.ex.PayParams;
import com.ty.ctr.ex.PayResultInterface;
import com.tystore.onlinepay.TyPay;

import org.cocos2dx.lib.Cocos2dxActivity;

public class AppActivity extends Cocos2dxActivity {

    private static AppActivity s_instance = null;
    public static AppActivity getInstance() { return s_instance; }
    private String apSecert;//ap密钥
    private String appId;	//应用ID
    private String chargeId;//计费代码
    private String  apName = "成都翼游互娱科技有限公司";//公司名称
    private String  appName = "易乐园商城";//APP名称
    private String  chargeName = "0.01元礼包";//道具名称
    private int  price;//价格 单位分
    private int  priceType = 1;//计费类型 1-按次计费；2-包月计费，此计费类型和chargeId类型一致
    private String  exdata ;
    private String  orderId;//AP自定义订单号，服务器透传对应txid字段
    private String channelId = "121";//AP自定义渠道号，服务器透传
    private String csPhoneNum = "4008689689";//AP客服电话

    /*
     * 按次计费测试产品参数
     */
    private String ciAppId = "1076644";
    private String ciChargeid = "265D4902E8CB4BCCE0530100007F6303";
    private String ciapSecert = "25FB4F3FE6822411E0530100007F66DE";

    /*
     * 包月计费测试产品参数
     */
    private String byAppid = "1075942";
    private String byChargeid = "32DD2CE9677269D9E0530100007F39DB";
    private String byapSecertd = "1FD9B6FAF17E3E54E0530100007FA781";
    Context context;
    PayParams mPayParams;
    TyPay mTyPay;
    BaseResponse baseResponse = new BaseResponse();
    private PayResultInterface mPayCallback = new PayResultInterface(){
        @Override
        public void execute(BaseResponse arg0) {
            // TODO Auto-generated method stub
            sendHander(handler ,arg0.getPayType() + " "+ arg0.getResult() + " " + arg0.getMsg() + " " +arg0.getOrdersn(),0);
        }

    };

    private long mkeyTime = 0;
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        //二次返回退出
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            if ((System.currentTimeMillis() - mkeyTime) > 2000) {
                mkeyTime = System.currentTimeMillis();
                Toast.makeText(this, "请再按一次退出游戏", Toast.LENGTH_LONG).show();
            } else {
                finish();
                System.exit(0);
            }
            return false;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mTyPay = TyPay.getInstance();
        mPayParams = new PayParams();
        mPayParams.setApName(apName);
        mPayParams.setAppid(appId);
        mPayParams.setAppName(appName);
        mPayParams.setChannelId(channelId);
        mPayParams.setCsPhone(csPhoneNum);
        mPayParams.setPayInterface(mPayCallback);

        this.context = this;
        this.s_instance = this;
        init();
        Log.e("onCreate","onCreate" + this);

    }


    public void init (){
        LinearLayout container = new LinearLayout(this);
        container.setOrientation(LinearLayout.VERTICAL);
        this.setContentView(container);
        Button submit3 = new Button(this);
        submit3.setText("0.01元按次计费");
        container.addView(submit3);
        submit3.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                orderId = ""+System.currentTimeMillis();
                appId = ciAppId;
                chargeId = ciChargeid;
                apSecert = ciapSecert;

                mPayParams.setApsecert(apSecert);
                mPayParams.setAppid(appId);
                priceType = 1;
                sendHander(handler ,"",1);
            }
        });

        Button submit2 = new Button(this);
        submit2.setText("0.1元包月计费");
        container.addView(submit2);
        submit2.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                orderId = ""+System.currentTimeMillis();
                priceType = 2;

                appId = byAppid;
                mPayParams.setAppid(appId);
                chargeId = byChargeid;
                apSecert = byapSecertd;
                price = 10;
                mPayParams.setApsecert(apSecert);
                mPayParams.setAppid(appId);
                sendHander(handler ,"",1);
            }
        });
        Button submit6 = new Button(this);
        submit6.setText("包月退订");
        container.addView(submit6);
        submit6.setOnClickListener(new OnClickListener() {

            @Override
            public void onClick(View v) {
                orderId = ""+System.currentTimeMillis();

                appId = byAppid;
                mPayParams.setAppid(appId);
                chargeId = byChargeid;
                apSecert = byapSecertd;

                mPayParams.setApsecert(apSecert);
                mPayParams.setAppid(appId);
                price = 10;
                sendHander(handler ,"",2);
            }
        });
    }

    public Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg)
        {
            if (!Thread.currentThread().isInterrupted())
            {
                switch (msg.what)
                {
                    case 0:
                        Toast.makeText(AppActivity.this, (String)msg.obj, Toast.LENGTH_LONG).show();
                        break;
                    case 1:
                        mTyPay.init(context, mPayParams);
                        mTyPay.pay(chargeId,orderId, chargeName, price, priceType,  exdata);
                        break;
                    case 2:
                        mTyPay.init(context,mPayParams);
                        mTyPay.quitPay(chargeId, orderId);
                        break;

                    default:
                        break;
                }
            }
        }
    } ;
    public void sendHander(Handler h, String sData, int flag){
        Message toMain = new Message();
        if (null != sData){
            toMain.obj = sData;
        }
        toMain.what = flag;
        h.sendMessage(toMain);
    }

    public void setParam(String schargeId,String schargeName,int sprice)
    {
        chargeId = schargeId;
        chargeName = schargeName;
        price = sprice;
        Log.i("cocos  activity",chargeId+" "+chargeName+ " "+price);
    }

    public int getBaseResponse()
    {
        Log.i("cocos  activity result:",String.valueOf(baseResponse.getResult()));
        return baseResponse.getResult();
    }
}
