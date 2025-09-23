# 📱 GitHub iOS 登录问题总结

## 问题现象
- 使用 Google 注册的 GitHub 账号，没有独立密码。
- 在 GitHub iOS App 登录时，App 默认跳到 **用户名+密码** 登录界面。
- 因为账号没有密码，输入邮箱和密码无法登录，报错This account does not support password sign-in：
## 排查过程
1. 一开始在 App 内尝试用邮箱 + 密码登录 → 始终失败。
2. 确认账号是用 **Google 登录** 注册的，确实没有 GitHub 独立密码。
3. 在 App 内置浏览器没看到 **Continue with Google** 入口。
4. 用 Safari 打开 [github.com/login](https://github.com/login)，发现可以正常用 Google 登录。

## 解决方案
- **推荐做法**  
1. 打开 Safari → 登录 GitHub → 选择 **Sign in with Google**。  
2. 登录成功后回到 GitHub iOS App，App 会自动识别 Safari 的登录会话。  
3. 进入 App 首页 → 成功登录。

- **可选方案**  
- 在 GitHub 网页版里（Settings → Password and authentication）设置一个独立密码。  
- 或者生成 **Personal Access Token (PAT)**，配合命令行 / SSH 使用。

## 总结
- 用 Google 注册的账号 = 没有 GitHub 密码。  
- iOS App 如果卡在“用户名+密码”界面 → 必须走 **Google 登录**。  
- Safari 登录一次后，App 会自动继承会话 → 成功进入首页。

---