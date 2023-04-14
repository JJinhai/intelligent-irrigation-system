const path = require('path')
const webpack = require('webpack');
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const HtmlWebpackPlugin = require('html-webpack-plugin');

const devMode = process.env.NODE_ENV !== 'production'

module.exports = {
  resolve: {
    extensions: [".js",".jsx"]
  },
  mode:devMode?'development':'production',
  devtool: devMode?'cheap-module-eval-source-map':'cheap-module-source-map',
  entry:["whatwg-fetch","./src/main.js"],
  output:{
    path:path.resolve(__dirname,'../dist'),
    filename:'[name].js',
    chunkFilename: '[name].js',
    publicPath:'/web/'
  },
  plugins:[
    new HtmlWebpackPlugin({
      title: 'operation site',
      template:'template/index.ejs'
    }),
    new MiniCssExtractPlugin({
      filename: "[name].css",
    }),
    new webpack.HashedModuleIdsPlugin(),
    new webpack.HotModuleReplacementPlugin(),
  ],
  module:{
    rules:[
      {
        test:/\.jsx?/,
        exclude: /node_modules/,
        use:'babel-loader'
      },
      {
        test: /\.css$/,
        include: /node_modules/,
        sideEffects: true,
        use:[
          devMode ? 'style-loader' : MiniCssExtractPlugin.loader,
          { loader: 'css-loader' },
        ]
      },
      {
        test: /\.less$/,
        // exclude: /(node_modules|..\/bPaaS_formula_fe)/,
        exclude: /node_modules/,
        sideEffects: true,
        use:[
          devMode ? 'style-loader' : MiniCssExtractPlugin.loader,
          { loader: 'css-loader', options: { importLoaders: 2 } },
          'postcss-loader',
          {
            loader:'less-loader',
            options:{
              javascriptEnabled: true,
            }
          },
        ]
      },
      {
        test: /\.css$/,
        // exclude: /(node_modules|..\/bPaaS_formula_fe)/,
        exclude: /node_modules/,
        sideEffects: true,
        use:[
          devMode ? 'style-loader' : MiniCssExtractPlugin.loader,
          { loader: 'css-loader', options: { importLoaders: 2 } },
          'postcss-loader',
        ]
      },
      {
        test:/.(png|svg|jpg|gif)$/,
        use: [
          {
            loader: 'url-loader',
            options: {
              limit: 8192,
              fallback:'file-loader'
            }
          }
        ]
      },
      {
        test: /\.(woff|woff2|eot|ttf|otf)$/,
        use: [
          {
            loader: 'url-loader',
            options: {
              limit: 8192,
              fallback:'file-loader'
            }
          }
        ]
      }
    ]
  }
}