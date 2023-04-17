const mockList = [
  '/web/state'
]


const getMockOptions = (api) =>{
  var option = {
    target: 'http://127.0.0.1:3000', // target host
    secure: false,
    changeOrigin: true,               // needed for virtual hosted sites
    ws: true,                         // proxy websockets
    pathRewrite: {}
  }
  option.pathRewrite[`^${api}`] = "/static" + api + ".json"
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




