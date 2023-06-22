# 编译工程
# bin/build.ps1
# --------------

# 通过 vswhere 找到 vs 的安装位置
$vsWhere = "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe"
$vsPath = & "$vsWhere" -products * -property installationPath

# 使用 devenv.com 的绝对路径编译项目
# 格式: 
#   devenv ${项目名称}.sln /Project ${项目名称} /Build [Debug|Release]
# 由于依赖库 crypto 是 Release 构建的，因此这里也只能用 Release
& "$vsPath\Common7\IDE\devenv.com" cpp.sln /Project cpp /Build Release
