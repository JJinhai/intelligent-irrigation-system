const express = require('express');
const webpack = require('webpack');
const webpackDevMiddleware = require('webpack-dev-middleware');

const app = express();

const proxy = require('http-proxy-middleware')
const proxyList = require('./proxy')

//做mock代理
Object.keys(proxyList).forEach( v =>{
  app.use(proxy(v,proxyList[v]))
})

var config;
if(process.argv.slice(2) == 'component'){
  config = require('./webpack.component.config.js');
}else{
  config = require('./webpack.config.js');
}
if(process.argv.slice(2) == 'map'){
  config.entry[2] = './src/pages/map.jsx'
}
config.entry = [...config.entry,'webpack-hot-middleware/client']

const compiler = webpack(config);
// 告诉 express 使用 webpack-dev-middleware，
// 以及将 webpack.config.js 配置文件作为基础配置
app.use(webpackDevMiddleware(compiler, {
  publicPath: config.output.publicPath
}));
app.use(require("webpack-hot-middleware")(compiler));

// 将文件 serve 到 port 3000。
app.listen(3000, function () {
  console.log('Example app listening on port 3000!\n');
});