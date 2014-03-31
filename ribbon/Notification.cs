using Microsoft.WindowsAPICodePack.Shell.PropertySystem;
using MS.WindowsAPICodePack.Internal;
using ribbon.Notif.ShellHelpers;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Windows.Data.Xml.Dom;
using Windows.UI.Notifications;

namespace ribbon.Notif
{
    class Notification
    {
        public static void notif(String title, String msg)
        {
            XmlDocument toastXml = ToastNotificationManager.GetTemplateContent(ToastTemplateType.ToastImageAndText02);

            // Fill in the text elements
            XmlNodeList stringElements = toastXml.GetElementsByTagName("text");

            stringElements[0].AppendChild(toastXml.CreateTextNode(title));
            stringElements[1].AppendChild(toastXml.CreateTextNode(msg));


            // Create the toast and attach event listeners
            ToastNotification toast = new ToastNotification(toastXml);
            // Show the toast. Be sure to specify the AppUserModelId on your application's shortcut!
            ToastNotificationManager.CreateToastNotifier(APP_ID).Show(toast);

        }

        public static bool TryCreateShortcut()
        {
            String shortcutPath = Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Microsoft\\Windows\\Start Menu\\Programs\\RibbonNotepad.lnk";
            if (!File.Exists(shortcutPath))
            {
                InstallShortcut(shortcutPath);
                return true;
            }
            return false;
        }

        private static void InstallShortcut(String shortcutPath)
        {
            // Find the path to the current executable
            String exePath = Process.GetCurrentProcess().MainModule.FileName;
            IShellLinkW newShortcut = (IShellLinkW)new CShellLink();

            // Create a shortcut to the exe
            
            ShellHelpers.ErrorHelper.VerifySucceeded(newShortcut.SetPath(exePath));
            ShellHelpers.ErrorHelper.VerifySucceeded(newShortcut.SetArguments(""));
            newShortcut.SetIconLocation(exePath, 1);
            // Open the shortcut property store, set the AppUserModelId property
            IPropertyStore newShortcutProperties = (IPropertyStore)newShortcut;

            using (PropVariant appId = new PropVariant(APP_ID))
            {
                ShellHelpers.ErrorHelper.VerifySucceeded(newShortcutProperties.SetValue(SystemProperties.System.AppUserModel.ID, appId));
                ShellHelpers.ErrorHelper.VerifySucceeded(newShortcutProperties.Commit());
            }

            // Commit the shortcut to disk
            IPersistFile newShortcutSave = (IPersistFile)newShortcut;

            ShellHelpers.ErrorHelper.VerifySucceeded(newShortcutSave.Save(shortcutPath, true));
        }
        private static String APP_ID = "MI.RIBBON_NOTEPAD";
    }
}
