@echo off
chcp 65001 >nul
echo ==============================================
echo   Keil MDK 编译缓存清理工具 (适配CubeMX工程)
echo ==============================================
echo.
echo 正在递归清理所有编译中间文件与输出文件...
echo.

:: ========== 编译中间文件 ==========
del *.bak /s /q
del *.ddk /s /q
del *.edk /s /q
del *.lst /s /q
del *.lnp /s /q
del *.mpf /s /q
del *.mpj /s /q
del *.obj /s /q
del *.omf /s /q
:: del *.opt /s /q  :: 禁止删除：保留J-Link调试配置与工程选项
del *.plg /s /q
del *.rpt /s /q
del *.tmp /s /q
del *.__i /s /q
del *.crf /s /q
del *.o /s /q
del *.d /s /q
del *.dep /s /q
del *.tra /s /q
del *.iex /s /q
del *.scvd /s /q

:: ========== 编译输出产物 ==========
del *.axf /s /q
del *.elf /s /q
del *.hex /s /q
del *.bin /s /q
del *.map /s /q
del *.sct /s /q

:: ========== 日志与网页报告 ==========
del *.htm /s /q
del *.html /s /q
del *.build_log.htm /s /q
del JLinkLog.txt /s /q
del *.log /s /q

echo.
echo 清理完成！
echo.
pause
exit