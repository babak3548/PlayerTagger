using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Player.DataControl;
using Player.Setting;

namespace Player
{
    public class Factory
    {

        public  Dictionary<Type  , object> ListObject = new Dictionary<Type, object>();

        public  object ReturnObjectByType(Type type)
        {
            foreach (var item in ListObject)
            {
                if (item.Key == type)
                {
                    return item.Value;
                }
            }
            var obj =  Activator.CreateInstance(type);
            ListObject.Add(type, obj);
            return obj;

        }

        public   PlayerControl CurrentPlayer(string FileExtension)
        {


            if (Player.Setting.Utility.IsImage(FileExtension))
                return (PlayerControl)ReturnObjectByType(typeof(picturePlayer));
            else if  (App.Setting.PlayerType == (int)EnumPlayeType.VlCPlayer)
                return (PlayerControl)ReturnObjectByType(typeof(VLCPlayer   ));
            //else if (App.Setting.PlayerType == (int)EnumPlayeType.LeadPlayer)
            //{ return (PlayerControl)ReturnObjectByType(typeof(LeadPlayer)); }
            else
            { return (PlayerControl)ReturnObjectByType(typeof(Player.DataControl.MediaPlayer)); }


        }
    }
}
