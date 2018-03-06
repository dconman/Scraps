using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace Scrap
{
    public class IsoTime
    {
        public static string GetOffset(DateTime time, TimeZoneInfo timeZone)
        {
            var offset = timeZone.GetUtcOffset(time);
            return (offset < TimeSpan.Zero ? "−" : "+") + offset.ToString(@"hh\:mm");
        }
        
        public static IEnumerable<string> TimeFormats(DateTime time, string offset, bool extended, bool midnight = false)
        {
            if( midnight && (time - time.Date) > TimeSpan.Zero)
                return new List<string>();
            var sep = extended ? ":" : "";
            long days, hours, minutes, seconds;
            double daysf, hoursf, minutesf, secondsf;
            long daysr, hoursr, minutesr, secondsr;
            long ticks = time.Ticks + (midnight ? TimeSpan.TicksPerDay : 0);
            daysf = ticks / (double) TimeSpan.TicksPerDay;
            days = Math.DivRem(time.Ticks, TimeSpan.TicksPerDay, out daysr);
            hoursf = daysr / (double) TimeSpan.TicksPerHour;
            hours = Math.DivRem(daysr, TimeSpan.TicksPerHour, out hoursr);
            minutesf = hoursr / (double) TimeSpan.TicksPerMinute;
            minutes = Math.DivRem(hoursr, TimeSpan.TicksPerMinute, out minutesr);
            secondsf = minutesr / (double) TimeSpan.TicksPerSecond;
            seconds = minutesr / TimeSpan.TicksPerSecond;
            var hoursS = hours.ToString("00");
            var hoursSF = ((hoursf-hours)*1000000).ToString("0000000");
            var minutesS = minutes.ToString("00");
            var minutesSF = ((minutesf-minutes)*1000000).ToString("0000000");
            var secondsS = seconds.ToString("00");
            var secondsSF = ((secondsf - seconds) * 1000000).ToString("0000000");
            return new List<string>
            {
                hoursS,
                hoursS + "," + hoursSF,
                hoursS + sep + minutesS,
                hoursS + sep + minutesS + "," + minutesSF,
                hoursS + sep + minutesS + sep + secondsS,
                hoursS + sep + minutesS + sep + secondsS + "," + secondsSF
            }.Select(str => str + offset);
        }
        
        public static IEnumerable<string> DatesNotForTimes(DateTime dateTime, bool midnight = false)
        {
            if( midnight && (dateTime - dateTime.Date) > TimeSpan.Zero)
                return new List<string>();
            
            var date = dateTime.AddDays(midnight ? -1 : 0).Date;
            
            var year = new DateTime(date.Year,1,4);
            var yow = (int) year.DayOfWeek;
            yow = (yow == 0 ? 6 : yow-1);
            var week = year.AddDays(0-yow);
            int doW;
            int woY = Math.DivRem((date - week).Days, 7, out doW) + 1;
            doW++;
            var doY = (date - year).Days + 4;
            return new List<string> {
                date.ToString("yyyy-MM-dd"),
                date.ToString("yyyyMMdd"),
                date.ToString("yyyy-MM"),
                date.ToString("yyyy-") + doY.ToString("000"),
                date.ToString("yyyy") + doY.ToString("000"),
                date.ToString("yyyy-") + "W" + woY.ToString("00-") + doW.ToString("0"),
                date.ToString("yyyy") + "W" + woY.ToString("00") + doW.ToString("0"),
                date.ToString("yyyy-") + "W" + woY.ToString("00"),
                date.ToString("yyyy") + "W" + woY.ToString("00"),
                date.ToString("yyyy")
                
            };
        }
        public static IEnumerable<string> DatesForTimes(DateTime dateTime, bool extended, bool midnight = false)
        {
            if( midnight && (dateTime - dateTime.Date) > TimeSpan.Zero)
                return new List<string>();
            
            var sep = extended ? "-" : "";
            
            var date = dateTime.AddDays(midnight ? -1 : 0).Date;
            
            var year = new DateTime(date.Year,1,4);
            var yow = (int) year.DayOfWeek;
            yow = (yow == 0 ? 6 : yow-1);
            var week = year.AddDays(0-yow);
            int doW;
            int woY = Math.DivRem((date - week).Days, 7, out doW) + 1;
            doW++;
            var doY = (date - year).Days + 4;
            return new List<string> {
                date.ToString("yyyy" + sep + "MM" + sep + "dd"),
                date.ToString("yyyy")  + sep + doY.ToString("000"),
                date.ToString("yyyy")  + sep + "W" + woY.ToString("00")  + sep + doW.ToString("0")
            };
        }
        
        public static void Main(string[] args)
        {
            var intTime = Convert.ToInt64(Console.ReadLine());

            var timeZone = TimeZoneInfo.FindSystemTimeZoneById("Central Standard Time");
            //timeZone.
            var dateTime = new DateTime(intTime, DateTimeKind.Utc);
            var local = TimeZoneInfo.ConvertTime(dateTime, timeZone).ToLocalTime();
            var offset = timeZone.GetUtcOffset(dateTime);
            var offsetString = (offset < TimeSpan.Zero ? "−" : "+") + offset.ToString(@"hh\:mm");
            var localTimes = TimeFormats(local, GetOffset(local, timeZone),true).Union(TimeFormats(local, GetOffset(local, timeZone),false));
            var localTimesM = TimeFormats(local, GetOffset(local, timeZone),true, true).Union(TimeFormats(local, GetOffset(local, timeZone),false,true));
            var utcTimes = TimeFormats(dateTime, "Z",true).Union(TimeFormats(dateTime, "Z",false));
            var utcTimesM = TimeFormats(dateTime, "Z",true,true).Union(TimeFormats(dateTime, "Z",false, true));
            var localDates = DatesNotForTimes(local);
            var localDatesM = DatesNotForTimes(local, true);
            var utcDates = DatesNotForTimes(dateTime);
            var utcDatesM = DatesNotForTimes(dateTime, true);
            var localDatesT = DatesForTimes(local,false).Union(DatesForTimes(local,true));
            var localDatesTM = DatesForTimes(local, false, true).Union(DatesForTimes(local, true, true));
            var utcDatesT = DatesForTimes(dateTime, false).Union(DatesForTimes(dateTime, true));
            var utcDatesTM = DatesForTimes(dateTime,false, true).Union(DatesForTimes(dateTime,true, true));
            var localDateTimes = from time in localTimes from date in localDatesT select date + "T" + time;
            var localDateTimesM = from time in localTimesM from date in localDatesTM select date + "T" + time;
            var utcDateTimes = from time in utcTimes from date in utcDatesT select date + "T" + time;
            var utcDateTimesM = from time in utcTimesM from date in utcDatesTM select date + "T" + time;
            
            var localPrint = localTimes.Union(localTimesM).Union(localDates).Union(localDatesM).Union(localDateTimes).Union(localDateTimesM);
            var utcPrint = utcTimes.Union(utcTimesM).Union(utcDates).Union(utcDatesM).Union(utcDateTimes).Union(utcDateTimesM);
            
            foreach(var str in localPrint.Union(utcPrint))
                Console.WriteLine(str);
            
        }
    }
}
