$(function(){
  var getCookie =function (objName){//获取指定名称的cookie的值
      var arrStr = document.cookie.split("; ");
      for(var i = 0;i < arrStr.length;i ++){
      var temp = arrStr[i].split("=");
      if(temp[0] == objName && objName=="UD") return decodeURIComponent(temp[1]);
      if(temp[0] == objName) return decodeURI(temp[1]);
      }
  }
  var tpl = '\<div class="popupbox">\
                <div class="popup" >\
                  <h3 class="popup-title"><a>博客皮肤升级</a></h3>\
                  <p>皮肤升级后将为您带来更舒适的阅读体验，更大的阅读空间！</p>\
                  <div class="popup-text">\
                    <p>9月19日前，优质博主抢先体验期</p>\
                    <p>9月21日起，所有用户陆续开放升级</p>\
                  </div>\
                  <div class="popup-center">\
                    <div class="popup-btn-box" >\
                      <span class="popupup-span" ><a class="popup-up">免费升级</a></span>\
                      <span class="popupwait-span" ><a class="popup-wait">以后再说</a></span>\
                    </div>\
                    <div class="popup-load" style="display:none;"><img src="http://static.blog.csdn.net/popupbox/img/load.png"></div>\
                    <div class="popup-success" style="display:none;">升级成功(<span class="popup-time">3</span>)</div>\
                  </div>\
                  <div class="popup-faq-box">\
                    <p class="popup-faq-title">FAQ</p>\
                    <div class="popup-faq-content">\
                      <dl>\
                        <dt><span>Q : </span> <span>我一定要升级吗？</span></dt>\
                        <dd><span>A : </span> <span class="popup-faq-span8">是的。9月21日起所有用户都将升级到新的博客皮肤。</span></dd>\
                        <dt><span>Q : </span> <span>我还可以更换为其它皮肤吗？</span></dt>\
                        <dd><span>A : </span> <span>为了体验和视觉效果的统一，以后将不再支持其他皮肤。</span></dd>\
                        <dt><span>欢迎和客服反馈意见和建议，我们会努力为大家提供更好的产品体验。</span></dt>\
                      </dl>\
                    </div>\
                  </div>\
                </div>\
                <div class="popupbox-mask">\
                </div>\
              </div>';
              
  $(document.body).prepend($(tpl));
  
  var cookieUserName = getCookie("UserName"),
      cookieUserInfo = getCookie("UserInfo")
  function isLogIn(){ //判断登陆
    return login = cookieUserName && cookieUserInfo ? true:false;
  }
  
  function initPopup(){ //初始判断
    if(isLogIn()){
      $.get('http://blog.csdn.net/'+cookieUserName+'/svc/IsChangeBlogSkin',function(data){
        if(parseInt(data) === 1){
          $('.popupbox').fadeIn(500)

        }
      })
    }
  }
  
  initPopup();
  
  var times = 3
  function popupbox(){ // popupbox 隐藏或跳转
    if(times == 0){
     var url= location.href+"";
     if(url.indexOf("article")>-1){
        if(cookieUserName === username){
          window.location.href = location.href+"?skintest=skin3-template-test";
        }else{
          $('.popupbox').fadeOut(500);
        } 
        return false;
      }else {
        $('.popupbox').fadeOut(500);
      }
    }  
    $('.popup-time').html(times--);
    setTimeout(popupbox,1000);  
  }
  
  function popupClickUp(){

    $.ajax({
      url: 'http://blog.csdn.net/'+cookieUserName+'/svc/SaveSkin',
      beforeSend:function(){
        $('.popup-btn-box').fadeOut(500,function(){
        });
        $('.popup-load').fadeIn(500);
      }, 
      success:function(data){
        if(data == 1){
          
          $('.popup-load').fadeOut(500,function(){
            $('.popup-success').fadeIn(500,function(){
              popupbox()
            });
          });
        }else{
          $('.popupbox').fadeOut(500);
          $.get('http://blog.csdn.net/'+ cookieUserName +'/svc/CancelSkin',function(data){
            console.log(data);
          })
        }
       }, 
      error:function(){
        $('.popup-load').fadeOut(500,function(){
          $('.popup-success').html('升级失败，请稍后再试').fadeIn(500,function(){
            popupbox()
          });
        });
      }
    })

  }
  function popupClose(){

    $.get('http://blog.csdn.net/'+ cookieUserName +'/svc/CancelSkin',function(data){
      console.log(data);
    })
    $('.popupbox').fadeOut(500);
  }
  $(document).on('click','.popup-up',popupClickUp)
  // close
  $(document).on('click','.popup-wait',popupClose)
})
$(function(){
  (function(){
      csdn.trackingAd('.popupwait-span', {
          pid: 'blog',
          mod: 'popu_478',
          mtp: '1'
      });
      csdn.trackingAd('.popupup-span', {
          pid: 'blog',
          mod: 'popu_477',
          mtp: '1'
      });
      csdn.trackingAd('.popup-title', {
        pid: 'blog',
        mod: 'popu_476',
        mtp: '1'
      });
  })()
})
