
set year=%date:~0,4%
echo year=%year%
set month=%date:~5,2%
echo month=%month%
set day=%date:~8,2%
echo day=%day%
set content_fail=未找到今日构建,请开发经理关注！
set title_fail=【%project%】%year%-%month%-%day%构建--未找到版本,无法进行测试！%ip%
java -jar TestMail.jar %receiver_fail% %title_fail% %content_fail%






