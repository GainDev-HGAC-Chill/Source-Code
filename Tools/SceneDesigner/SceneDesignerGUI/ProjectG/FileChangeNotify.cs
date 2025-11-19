/*///////////////////////////////////////////////////
* FileChangeNotify 09.03.04 Source Flyback and Rebuild
* Tells when a file with the specified extension is changed in the specified path.
* More than one change message for one change
* For example, in the case of file modification, the modification date and the access date are changed.
* The phenomenon that appears. It handles this filtering once.
 * /////////////////////////////////////////////////*/

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace Emergent.Gamebryo.SceneDesigner.GUI.ProjectG
{
	class FileChangeNotify
	{
		private FileSystemWatcher	m_kWatcher = new FileSystemWatcher();
		private String m_kTargetPath;
		private String m_kTargetExtend;
		private NotifyFilters m_kTargetFilter;
		private bool m_bIncludeSubDir;

		//외부에서 연결할 핸들러
		// Handles external connection
		public delegate void OuterHandler(object kSender, FileSystemEventArgs kEvent, RenamedEventArgs kRenameEvent);
		public OuterHandler PfnOuterHandler = null;
		
		//파일변경 메세지 중복시 걸러내기 위한 변수
		// Variable to duplicate file change message
		private String m_kLastChangedFileName; // Last changed variable (마지막으로 변경된 변수)
		private DateTime m_kLastWriteTime;          // Date and time of content change (마지막으로 내용이 변경된 날짜와 시간)

		public OuterHandler ChangedHandler
		{
			set
			{
				PfnOuterHandler = value;
			}
		}

		private bool IsOverlappedLastWriteTime(object kSender, String kFullPath)
		{
			FileInfo kFi = new FileInfo(kFullPath);
			if ((m_kLastChangedFileName == kFullPath) && (kFi.LastWriteTime == m_kLastWriteTime))
			{
				return true;
			}
			else if ((m_kLastChangedFileName == kFullPath) && (kFi.LastWriteTime != m_kLastWriteTime))
			{
				m_kLastWriteTime = kFi.LastWriteTime;
				return false;
			}
			else
			{
				m_kLastWriteTime = kFi.LastWriteTime;
				m_kLastChangedFileName = kFullPath;
				return false;
			}
		}

		private void fcn_rename(object kSender, RenamedEventArgs kEvent)
		{
			if (null != PfnOuterHandler)
			{
				PfnOuterHandler(kSender, null, kEvent);
			} 
		}
		private void fcn_changed(object kSender, FileSystemEventArgs kEvent)
		{
			if (false == IsOverlappedLastWriteTime(kSender, kEvent.FullPath))
			{
				if (null != PfnOuterHandler)
				{
					PfnOuterHandler(kSender, kEvent, null);
				}
			}			
		}

		private void fcn_deleted(object kSender, FileSystemEventArgs kEvent)
		{
			if (null != PfnOuterHandler)
			{
				PfnOuterHandler(kSender, kEvent, null);
			}
		}
		private void fcn_created(object kSender, FileSystemEventArgs kEvent)
		{
			if (null != PfnOuterHandler)
			{
				PfnOuterHandler(kSender, kEvent, null);
			} 
		}

		public string GetChangedFileFullPath()
		{
			return m_kLastChangedFileName;
		}

		public FileChangeNotify(String kPath, String kExtend, NotifyFilters kFilter, bool bIncludeSubDir)
		{
			m_kTargetPath = kPath;
			m_kTargetExtend = kExtend;
			m_kTargetFilter = kFilter;
			m_bIncludeSubDir = bIncludeSubDir;

			m_kWatcher.Path = kPath;
			m_kWatcher.Filter = kExtend;
			m_kWatcher.NotifyFilter = kFilter;
			m_kWatcher.IncludeSubdirectories = bIncludeSubDir;

			m_kWatcher.Renamed += new RenamedEventHandler(fcn_rename);
			m_kWatcher.Changed += new FileSystemEventHandler(fcn_changed);
			m_kWatcher.Deleted += new FileSystemEventHandler(fcn_deleted);
			m_kWatcher.Created += new FileSystemEventHandler(fcn_created);
		}

		public void Start()
		{
			m_kWatcher.EnableRaisingEvents = true;
		}

		public void Stop()
		{
			m_kWatcher.EnableRaisingEvents = false;
		}
	}
}
