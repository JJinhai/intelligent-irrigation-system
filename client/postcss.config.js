/**
 * file: extname, dirname, basename
 * env: process.env.NODE_ENV
 * options: webpack options.config.ctx
 */
module.exports = ({ file, options, env }) =>{
  return {
    plugins: [
      require('postcss-import')(),
      // require('stylelint')(),
      require('postcss-preset-env')(),
      // require('autoprefixer')(),
      require('cssnano')()
    ]
  }
}