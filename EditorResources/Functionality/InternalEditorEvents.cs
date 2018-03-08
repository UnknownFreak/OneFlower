using EditorResources.UserControls;
using System;
using System.Collections.ObjectModel;

namespace EditorResources.Functionality
{
    public static class InternalEditorEvents
    {
        public static EventHandler<RequestObjectDataListEventArgs> onRequestObjectDataList;

        public static void OnRequsetObjectDataListEvent(RequestObjectDataListEventArgs args)
        {
            onRequestObjectDataList?.Invoke(null, args);
        }

        public class RequestObjectDataListEventArgs : EventArgs
        {
            internal ObservableCollection<ObjectDataViewModel> Observable { get; set; }
        }

        public static EventHandler requestObjectData;
        
        public static void RequestObjectData()
        {
            requestObjectData?.Invoke(null, EventArgs.Empty);
        }

        public static void Log(String message, Utils.Message.MsgType logAs)
        {
            RequestEvents.OnLogEvent(new RequestEvents.EditorLogEventArgs() { logMessage = new Utils.Message() { message = message, type = logAs}});
        }
    }
}
