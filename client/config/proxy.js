const mockList = [
  '/a'
]


const getMockOptions = (api) =>{
  var option = {
    target: '127.0.0.1', // target host
    changeOrigin: true,               // needed for virtual hosted sites
    ws: true,                         // proxy websockets
    pathRewrite: {}
  }
  option.pathRewrite[`^${api}`] = api
  return option
};

function createProxyList(){
  var obj = { };
  var apiList = mockList || [];
  var getOptions = getMockOptions;
  apiList.forEach( v =>{
    obj[v] = getOptions(v)
  })
  return obj
}
module.exports = createProxyList([mockList ,getMockOptions])




