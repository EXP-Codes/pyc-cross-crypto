# 编译工程
# bin/build.ps1
# --------------

# 设置 VS2022 的安装路径到 PATH 环境变量，以便使用 devenv 命令行
# 建议根据实际情况设置到系统环境变量，而不是在命令行设置
# set PATH=%PATH%;"S:\04_work\MicrosoftVisualStudio\2022\Community\Common7\IDE"

# 格式: 
#   devenv ${项目名称}.sln /Project ${项目名称} /Build [Debug|Release]
# 由于依赖库 crypto 是 Release 构建的，因此这里也只能用 Release
devenv cpp.sln /Project cpp /Build Release