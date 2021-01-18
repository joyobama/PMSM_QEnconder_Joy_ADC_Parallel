# PMSM_QEnconder_Joy_ADC_Parallel
2021年1月3日开始使用的电机驱动程序

数据类型变换表
### 有符号数的转换
<table style="width: 921px; height: 691px" border="10">
<tbody>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">原类型</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">目标类型</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换方法</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">&nbsp;char</span></td>
<td style="text-align: center">
<p><span style="font-family: 宋体; font-size: 15px">short</span></p>
</td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">最高符号位失去位意义，变为数据位</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到short；然后从short转到unsigned short</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转换到unsigned long</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">float</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转到float</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转换到double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转换到long double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center">
<p><span style="font-family: 宋体; font-size: 15px">最高为失去意义，变为数据位</span></p>
</td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转到unsigned long</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">float</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转到float</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转到double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">符号位扩展到long；然后从long转换到long double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">最高为失去意义，变为数据位</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">float</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">使用单精度浮点数表示，可能失去精度</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">使用单精度浮点数表示，可能失去精度</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">使用单精度浮点数表示，可能失去精度</span></td>
</tr>
</tbody>
</table>



### 有符号数的转换
<table style="width: 930px; height: 675px" border="10">
<tbody>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">原类型</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">目标类型</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换方法</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">最高为作符号位</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">0扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">0扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">0扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">0扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">float</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到float</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到long double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">最高为作符号位</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">0扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">0扩展</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">float</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到float</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到long double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">最高位作符号位</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned char</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned short</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">保留低位字节</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">float</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到float</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">直接转换到double</span></td>
</tr>
<tr>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">unsigned long</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">long double</span></td>
<td style="text-align: center"><span style="font-family: 宋体; font-size: 15px">转换到long；然后从long转换到long double</span></td>
</tr>
</tbody>
</table>

### 标准C数据长度与DSP数据长度

![标准C数据类型长度](https://images0.cnblogs.com/blog/702782/201501/121635015588495.jpg "标准C数据类型长度")

![DSP数据类型长度](http://editerupload.eepw.com.cn/201407/9ad430605c7b699eaeec0f90ccd8e360.jpg "DSP数据长度")
