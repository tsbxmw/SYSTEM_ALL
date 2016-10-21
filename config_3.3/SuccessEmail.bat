::服务器路径
echo server=%server%
::构建版本前缀
echo version_pre=%version_pre%
::本地路径
echo local_path=%local_path%
::成功找到今日构建
::多个收件人分号分隔
echo receiver_success=%receiver_success%
::邮件标题
set title_success=【%project%】%year%-%month%-%day%构建--已找到版本，准备开始下载测试！%ip%
echo title_success=%title_success%
::邮件正文
set content_success=成功找到今日构建！
echo content_success=%content_success%

::未找到今日构建
::多个收件人分号分隔
echo receiver_fail=%receiver_fail%
::邮件标题
set title_fail=【%project%】%year%-%month%-%day%构建--未找到版本,无法进行测试！%ip%
echo title_fail=%title_fail%
::邮件正文
set content_fail=未找到今日构建,请开发经理关注！
echo content_fail=%content_fail%
::本地版本文件
set local_version_file=E:\version\P809V50\P809V50.zip
echo local_version_file=%local_version_file%
if exist %local_version_file% (
echo download over!
echo A | "C:\Program Files\HaoZip\HaoZipC.exe" e E:\version\P809V50\P809V50.zip -o%local_path%

java -jar TestMail.jar %receiver_success% %title_success% %content_success%
) else (
   java -jar TestMail.jar %receiver_fail% %title_fail% %content_fail%
    )

    
goto :eof

:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::	子程序：延时
::		延时长度为 参数*10秒
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:DELAY
for /l %%Z in (%1,-1,0) do (ping 10.0.0.127 -w 10000 -n 1 >nul)
goto :eof

pause