const merge = require("webpack-merge");
const baseConfig = require('./webpack.config')
const path = require('path')
const CleanWebpackPlugin = require('clean-webpack-plugin');
const BundleAnalyzerPlugin = require('webpack-bundle-analyzer').BundleAnalyzerPlugin;

module.exports = mode => {

  var prodConfig = {
    plugins:[
      new CleanWebpackPlugin(),
      // new BundleAnalyzerPlugin()
    ]
  }
  return merge(baseConfig,prodConfig)
}