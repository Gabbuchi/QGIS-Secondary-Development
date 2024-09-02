笔记在wiki里

## 主界面
基于qgis二次开发，主要开发诸如工程文件读取、图层添加、基本显示工具插件（例如放大缩小移动等）、鼠标框选的要素读取、要素样式修改、根据经纬度添加marker等基本功能
![image](https://github.com/Gabbuchi/QGIS-Secondary-Development/blob/ver.5/pictures/%E4%B8%BB%E7%95%8C%E9%9D%A2.png)

## 要素读取
重写qgsfeatureidentify下的鼠标操作方法，实现框选功能，将数据存储并用tableview展示
![image](https://github.com/Gabbuchi/QGIS-Secondary-Development/blob/ver.5/pictures/%E8%A6%81%E7%B4%A0%E8%AF%BB%E5%8F%96.png)

## 要素样式修改
Qgis的样式设置主要继承自抽象类QgsSymbol，QgsFillSymbol主要是针对填充图层（也就是面图层）、QgsLineSymbol主要针对线图层、QgaMarker主要针对点图层
![image](https://github.com/Gabbuchi/QGIS-Secondary-Development/blob/ver.5/pictures/%E8%A6%81%E7%B4%A0%E4%BF%AE%E6%94%B9.png)
![image](https://github.com/Gabbuchi/QGIS-Secondary-Development/blob/ver.5/pictures/symbol.png)

## 图层叠加
在中国大陆图层的基础上添加全国路网图层，并同时实现图层分层选择及要素读取功能，后续基于路网图层和pgrouting添加路径规划功能
![image](https://github.com/Gabbuchi/QGIS-Secondary-Development/blob/ver.5/pictures/%E5%9B%BE%E5%B1%82%E5%8F%A0%E5%8A%A0.png)

## marker添加
输入经纬度，在指定区域添加marker
![image](https://github.com/Gabbuchi/QGIS-Secondary-Development/blob/ver.5/pictures/marker%E6%B7%BB%E5%8A%A0.png)
