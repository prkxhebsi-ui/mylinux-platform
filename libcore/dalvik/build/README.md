MyLinux Dalvik Java build

build-dalvik-config-jar.sh compiles ToolDescriptor.java
and packages it with the module resources.

RuntimeConfig.java is not included yet because it depends
on org.json.JSONObject. It will be added when the JSON
library source or compiled dependency is available.
