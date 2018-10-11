using EditorResources.UserControls;
using System;
using System.Collections.ObjectModel;

namespace EditorResources.Utils
{
    public static class InternalEditorEvents
    {

        public static void OnRequsetObjectDataListEvent(RequestObjectDataListEventArgs args) => onRequestObjectDataList?.Invoke(null, args);

        public static void RequestObjectData() => requestObjectData?.Invoke(null, EventArgs.Empty);

        public static void Log(String message, Message.MsgType logAs)
        {
            EditorEvents.OnLogEvent(new EditorEvents.EditorLogEventArgs() { logMessage = new Message() { message = message, type = logAs } });
        }

        public static EventHandler<RequestObjectDataListEventArgs> onRequestObjectDataList;
        public static EventHandler requestObjectData;

        public class RequestObjectDataListEventArgs : EventArgs
        {
            internal ObservableCollection<ObjectDataViewModel> Observable { get; set; }
        }
    }
}
