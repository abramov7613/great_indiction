/*
    MIT License

    Copyright (c) 2026 Vladimir Abramov <abramov7613@yandex.ru>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/
#include "great_indiction.h"
#include <array>
#include <stdexcept>
#include <bitset>
#include <optional>


namespace {

using namespace great_indiction ;
using DayProperties = std::optional<std::bitset<static_cast<unsigned>(DAY_PROPERTY_ENUM_SIZE_)>> ;
using MonthProperties = std::array<DayProperties, 31> ;
using YearProperties = std::array<MonthProperties, 12> ;


constexpr void check_year_number(const int year_number_in_great_indiction)
{
  if (year_number_in_great_indiction < 1 || year_number_in_great_indiction > 532)
    throw std::runtime_error("value of 'year_number_in_great_indiction' must be in range [1,533)");
}


consteval auto calc_easter_for(const int year_number_in_great_indiction)
{ //use Gauss method for julian calendar
  check_year_number(year_number_in_great_indiction) ;
  const int year = year_number_in_great_indiction + 1940 ;
  int m_= 3,
      a = year % 19,
      b = year % 4,
      c = year % 7,
      d = (19*a+15) % 30,
      e = (2*b+4*c+6*d+6) % 7,
      p = 22 + d + e;
  if(p>31) {
    p = d + e - 9;
    m_ = 4;
  }
  return std::make_pair(m_, p);
}


consteval const auto calc_easter_dates_array()
{
  // index+1 = number of year in great indiction
  // first = month of orthodox easter
  // second = day of orthodox easter
  std::array<MonthDay, 532> result;
  for (size_t i=0; i<result.size(); ++i) result[i] = calc_easter_for(i+1) ;
  return result;
}


constexpr auto easter_dates_array = calc_easter_dates_array();


consteval bool is_leap(const int year_number_in_great_indiction)
{
  check_year_number(year_number_in_great_indiction) ;
  const int year = year_number_in_great_indiction + 1940 ;
  return (year%4 == 0) ;
}


consteval int month_length(const int month, const bool leap)
{
  switch(month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
        break;
    case 2:
        return leap ? 29 : 28;
        break;
    default:
        return 0;
  }
}


consteval void check_date(const int year_number_in_great_indiction, const MonthDay date)
{
  if (year_number_in_great_indiction < 1 || year_number_in_great_indiction > 532)
    throw "value of 'year_number_in_great_indiction' must be in range [1,533)";
  if (date.first < 1 || date.first > 12)
    throw "invalid month number";
  if (date.second < 1 || date.second > month_length(date.first, is_leap(year_number_in_great_indiction)))
    throw "invalid day number";
}


consteval int days_count_from_1jan_to(const int year_number_in_great_indiction, const MonthDay date)
{
  check_date(year_number_in_great_indiction, date) ;
  int r = 0,
      m = date.first,
      d = date.second;
  while(1){
    r += d;
    if (!--m) break;
    d = month_length(m, is_leap(year_number_in_great_indiction));
  }
  return r;
}


consteval int calc_apostol_fast_length_for(const int year_number_in_great_indiction)
{
  const int y = year_number_in_great_indiction ;
  check_year_number(y) ;
  const int x1 = days_count_from_1jan_to(y, easter_dates_array[y-1]) ;
  const int x2 = days_count_from_1jan_to(y, {6,29}) ;
  return x2 - x1 - 56;
}


consteval const auto calc_apostol_fast_length_array()
{
  // index+1 = number of year in great indiction
  std::array<int, 532> result;
  for (size_t i=0; i<result.size(); ++i) result[i] = calc_apostol_fast_length_for(i+1) ;
  return result;
}


constexpr auto apostol_fast_length_array = calc_apostol_fast_length_array() ;


consteval int fdiv_(int a, int b)
{//floor division
  return (a - (a < 0 ? b - 1 : 0)) / b;
}


consteval auto incd_(const MonthDay date, const bool leap, const int days=1)
{
  MonthDay r {date};
  MonthDay l {date};
  if(days<1) { return l; }
  if(date.first<1 || date.first>12)  { return l; }
  int u = month_length(date.first, leap);
  if(date.second<1 || date.second>u) { return l; }
  r.second += days;
  while (r.second>u) {
    r.second = r.second - u;
    r.first++;
    if(r.first>12) return l;
    u = month_length(r.first, leap);
  }
  return r;
}


consteval auto decd_(const MonthDay date, const bool leap, const int days=1)
{
  MonthDay r {date};
  MonthDay l {date};
  if(days<1) { return l; }
  if(date.first<1 || date.first>12)  { return l; }
  int u = month_length(date.first, leap);
  if(date.second<1 || date.second>u) { return l; }
  r.second = r.second - days;
  while (r.second < 1) {
    r.first--;
    if(r.first<1) return l;
    u = month_length(r.first, leap);
    r.second = u + r.second;
  }
  return r;
}


consteval int calc_weekday_for(const int year_number_in_great_indiction, const MonthDay date)
{
  check_date(year_number_in_great_indiction, date) ;
  int y = year_number_in_great_indiction + 1940,
      m = date.first,
      d = date.second,
      c0 = fdiv_((m - 3) , 12), // Dr Louis Strous's method
      j1 = fdiv_(1461 * (y + c0), 4),
      j2 = fdiv_(153 * m - 1836 * c0 - 457, 5),
      cjdn = j1 + j2 + d + 1721117;
  return (cjdn+1) % 7; // 0=вс, 1=пн, 2=вт ...
}


consteval const YearProperties calc_year_properties_for(const int year_number_in_great_indiction)
{
  const int year = year_number_in_great_indiction ;
  check_year_number(year) ;
  const bool leap = is_leap(year) ;
  YearProperties result;
  for (size_t m = 0; m < result.size(); ++m) for (size_t d = 0; d < result[m].size(); ++d) {
    if (static_cast<long long>(d) >= month_length(m+1, leap)) continue ;
    result[m][d] = DayProperties::value_type{} ;
  }
  auto set_result_value = [&result](const MonthDay date, const DayProperty value) consteval {
    result[date.first-1][date.second-1].value().set(static_cast<unsigned>(value));
  };
  // точки отсчета
  auto const pasha = easter_dates_array[year-1];
  auto const ascension = incd_(pasha, leap, 39);
  auto const pentecost = incd_(ascension, leap, 10);
  auto const all_saints = incd_(pentecost, leap, 7);
  auto const publican_pharisee = decd_(pasha, leap, 70);
  auto const prodigal_son = incd_(publican_pharisee, leap, 7);
  auto const dread_judgement = incd_(publican_pharisee, leap, 14);
  auto const forgiveness = incd_(publican_pharisee, leap, 21);
  auto const lent_begin = incd_(forgiveness, leap, 1);
  auto const palm_sun = incd_(lent_begin, leap, 41);
  // Сре́тение Господа Бога и Спаса нашего Иисуса Христа
  MonthDay dd = {2,2},
           t1 = incd_(publican_pharisee, leap, 13),
           t2 = {},
           t3 = {2, 9};
  if (dd >= lent_begin) dd = forgiveness;
  set_result_value(dd, GOD_MEETING);
  if (dd == t1) t1 = incd_(publican_pharisee, leap, 6);
  set_result_value(t1, MEMORIAL_SAT);
  auto const memorial_sat = t1;
  //Предпразднство Сре́тения
  if(dd != MonthDay(2, 1)) {
    MonthDay x (2, 1);
    if(x == t1) x = decd_(x, leap, 1);
    set_result_value(x, FOREFEAST_GOD_MEETING);
  }
  //отдание праздника Сре́тения
  t1 = prodigal_son;
  t2 = incd_(t1, leap, 2);
  if(dd>=t1 && dd<=t2) {
    t3 = incd_(t1, leap, 5);
  }
  t1 = t2 = incd_(t1, leap, 3);
  if(dd>=t1 && dd<=t2) {
    t3 = incd_(dread_judgement, leap, 2);
  }
  t1 = dread_judgement;
  t2 = incd_(dread_judgement, leap, 1);
  if(dd>=t1 && dd<=t2) {
    t3 = incd_(dread_judgement, leap, 4);
  }
  t1 = incd_(dread_judgement, leap, 2);
  t2 = incd_(dread_judgement, leap, 3);
  if(dd>=t1 && dd<=t2) {
    t3 = incd_(dread_judgement, leap, 6);
  }
  t1 = incd_(dread_judgement, leap, 4);
  t2 = incd_(dread_judgement, leap, 6);
  if(dd>=t1 && dd<=t2) {
    t3 = forgiveness;
  }
  if(dd != forgiveness) {
    if(t3 == memorial_sat) t3 = decd_(t3, leap, 1);
    set_result_value(t3, ENDOF_GOD_MEETING);
  }
  //Попразднствa Сретения Господня
  t2 = t1 = incd_(dd, leap, 1);
  int i = 1;
  if(dd != forgiveness && t3 != t1) {
    do {
      if(t2 == memorial_sat) {
        t2 = incd_(t2, leap, 1);
        if(t2>=t3) break;
      }
      switch(i) {
        case 1:
          set_result_value(t2, AFTERFEAST_GOD_MEETING1);
          break;
        case 2:
          set_result_value(t2, AFTERFEAST_GOD_MEETING2);
          break;
        case 3:
          set_result_value(t2, AFTERFEAST_GOD_MEETING3);
          break;
        case 4:
          set_result_value(t2, AFTERFEAST_GOD_MEETING4);
          break;
        case 5:
          set_result_value(t2, AFTERFEAST_GOD_MEETING5);
          break;
        case 6:
          set_result_value(t2, AFTERFEAST_GOD_MEETING6);
          break;
      };
      t2 = incd_(t2, leap, 1);
      i++;
    } while (t2 != t3);
  }
  // Двунадесятые переходящие праздники
  set_result_value(palm_sun,       MOVEABLE_FEAST);
  set_result_value(ascension,      MOVEABLE_FEAST);
  set_result_value(pentecost,      MOVEABLE_FEAST);
  // Двунадесятые непереходящие праздники
  set_result_value( dd,       IMMOVEABLE_FEAST);
  set_result_value({1,6},     IMMOVEABLE_FEAST);
  set_result_value({3,25},    IMMOVEABLE_FEAST);
  set_result_value({8,6},     IMMOVEABLE_FEAST);
  set_result_value({8,15},    IMMOVEABLE_FEAST);
  set_result_value({9,8},     IMMOVEABLE_FEAST);
  set_result_value({9,14},    IMMOVEABLE_FEAST);
  set_result_value({11,21},   IMMOVEABLE_FEAST);
  set_result_value({12,25},   IMMOVEABLE_FEAST);
  // великие праздники
  set_result_value({1,1},    GREAT_FEAST);
  set_result_value({6,24},   GREAT_FEAST);
  set_result_value({6,29},   GREAT_FEAST);
  set_result_value({8,29},   GREAT_FEAST);
  set_result_value({10,1},   GREAT_FEAST);
  // от Недели о мытаре́ и фарисе́е до дня Всех святых.
  set_result_value(publican_pharisee                 , PUBLICAN_PHARISEE_SUN);
  set_result_value(prodigal_son                      , PRODIGAL_SON_SUN);
  set_result_value(dread_judgement                   , DREAD_JUDGEMENT_SUN);
  set_result_value(incd_(dread_judgement, leap, 1)   , CHEESE_MON);
  set_result_value(incd_(dread_judgement, leap, 2)   , CHEESE_TUE);
  set_result_value(incd_(dread_judgement, leap, 3)   , CHEESE_WED);
  set_result_value(incd_(dread_judgement, leap, 4)   , CHEESE_THU);
  set_result_value(incd_(dread_judgement, leap, 5)   , CHEESE_FRI);
  set_result_value(incd_(dread_judgement, leap, 6)   , CHEESE_SAT);
  set_result_value(forgiveness                       , CHEESE_SUN);
  set_result_value(lent_begin                        , LENT_WEEK1_MON);
  set_result_value(incd_(lent_begin, leap, 1), LENT_WEEK1_TUE);
  set_result_value(incd_(lent_begin, leap, 2), LENT_WEEK1_WED);
  set_result_value(incd_(lent_begin, leap, 3), LENT_WEEK1_THU);
  set_result_value(incd_(lent_begin, leap, 4), LENT_WEEK1_FRI);
  set_result_value(incd_(lent_begin, leap, 5), LENT_WEEK1_SAT);
  set_result_value(incd_(lent_begin, leap, 6), LENT_SUN1);
  set_result_value(incd_(lent_begin, leap, 7), LENT_WEEK2_MON);
  set_result_value(incd_(lent_begin, leap, 8), LENT_WEEK2_TUE);
  set_result_value(incd_(lent_begin, leap, 9), LENT_WEEK2_WED);
  set_result_value(incd_(lent_begin, leap, 10), LENT_WEEK2_THU);
  set_result_value(incd_(lent_begin, leap, 11), LENT_WEEK2_FRI);
  set_result_value(incd_(lent_begin, leap, 12), LENT_WEEK2_SAT);
  set_result_value(incd_(lent_begin, leap, 13), LENT_SUN2);
  set_result_value(incd_(lent_begin, leap, 14), LENT_WEEK3_MON);
  set_result_value(incd_(lent_begin, leap, 15), LENT_WEEK3_TUE);
  set_result_value(incd_(lent_begin, leap, 16), LENT_WEEK3_WED);
  set_result_value(incd_(lent_begin, leap, 17), LENT_WEEK3_THU);
  set_result_value(incd_(lent_begin, leap, 18), LENT_WEEK3_FRI);
  set_result_value(incd_(lent_begin, leap, 19), LENT_WEEK3_SAT);
  set_result_value(incd_(lent_begin, leap, 20), LENT_SUN3);
  set_result_value(incd_(lent_begin, leap, 21), LENT_WEEK4_MON);
  set_result_value(incd_(lent_begin, leap, 22), LENT_WEEK4_TUE);
  set_result_value(incd_(lent_begin, leap, 23), LENT_WEEK4_WED);
  set_result_value(incd_(lent_begin, leap, 24), LENT_WEEK4_THU);
  set_result_value(incd_(lent_begin, leap, 25), LENT_WEEK4_FRI);
  set_result_value(incd_(lent_begin, leap, 26), LENT_WEEK4_SAT);
  set_result_value(incd_(lent_begin, leap, 27), LENT_SUN4);
  set_result_value(incd_(lent_begin, leap, 28), LENT_WEEK5_MON);
  set_result_value(incd_(lent_begin, leap, 29), LENT_WEEK5_TUE);
  set_result_value(incd_(lent_begin, leap, 30), LENT_WEEK5_WED);
  set_result_value(incd_(lent_begin, leap, 31), LENT_WEEK5_THU);
  set_result_value(incd_(lent_begin, leap, 32), LENT_WEEK5_FRI);
  set_result_value(incd_(lent_begin, leap, 33), LENT_WEEK5_SAT);
  set_result_value(incd_(lent_begin, leap, 34), LENT_SUN5);
  set_result_value(incd_(lent_begin, leap, 35), LENT_WEEK6_MON);
  set_result_value(incd_(lent_begin, leap, 36), LENT_WEEK6_TUE);
  set_result_value(incd_(lent_begin, leap, 37), LENT_WEEK6_WED);
  set_result_value(incd_(lent_begin, leap, 38), LENT_WEEK6_THU);
  set_result_value(incd_(lent_begin, leap, 39), LENT_WEEK6_FRI);
  set_result_value(incd_(lent_begin, leap, 40), LENT_WEEK6_SAT);
  set_result_value(palm_sun                   , LENT_SUN7);
  set_result_value(incd_(lent_begin, leap, 42), LENT_WEEK7_MON);
  set_result_value(incd_(lent_begin, leap, 43), LENT_WEEK7_TUE);
  set_result_value(incd_(lent_begin, leap, 44), LENT_WEEK7_WED);
  set_result_value(incd_(lent_begin, leap, 45), LENT_WEEK7_THU);
  set_result_value(incd_(lent_begin, leap, 46), LENT_WEEK7_FRI);
  set_result_value(incd_(lent_begin, leap, 47), LENT_WEEK7_SAT);
  set_result_value(pasha, EASTER);
  set_result_value(incd_(pasha, leap, 1), BRIGHT_MON);
  set_result_value(incd_(pasha, leap, 2), BRIGHT_TUE);
  set_result_value(incd_(pasha, leap, 3), BRIGHT_WED);
  set_result_value(incd_(pasha, leap, 4), BRIGHT_THU);
  set_result_value(incd_(pasha, leap, 5), BRIGHT_FRI);
  set_result_value(incd_(pasha, leap, 6), BRIGHT_SAT);
  set_result_value(incd_(pasha, leap, 7), SUN2_AFTER_EASTER);
  set_result_value(incd_(pasha, leap, 8), WEEK2_AFTER_EASTER_MON);
  set_result_value(incd_(pasha, leap, 9), WEEK2_AFTER_EASTER_TUE);
  set_result_value(incd_(pasha, leap, 10), WEEK2_AFTER_EASTER_WED);
  set_result_value(incd_(pasha, leap, 11), WEEK2_AFTER_EASTER_THU);
  set_result_value(incd_(pasha, leap, 12), WEEK2_AFTER_EASTER_FRI);
  set_result_value(incd_(pasha, leap, 13), WEEK2_AFTER_EASTER_SAT);
  set_result_value(incd_(pasha, leap, 14), SUN3_AFTER_EASTER);
  set_result_value(incd_(pasha, leap, 15), WEEK3_AFTER_EASTER_MON);
  set_result_value(incd_(pasha, leap, 16), WEEK3_AFTER_EASTER_TUE);
  set_result_value(incd_(pasha, leap, 17), WEEK3_AFTER_EASTER_WED);
  set_result_value(incd_(pasha, leap, 18), WEEK3_AFTER_EASTER_THU);
  set_result_value(incd_(pasha, leap, 19), WEEK3_AFTER_EASTER_FRI);
  set_result_value(incd_(pasha, leap, 20), WEEK3_AFTER_EASTER_SAT);
  set_result_value(incd_(pasha, leap, 21), SUN4_AFTER_EASTER);
  set_result_value(incd_(pasha, leap, 22), WEEK4_AFTER_EASTER_MON);
  set_result_value(incd_(pasha, leap, 23), WEEK4_AFTER_EASTER_TUE);
  set_result_value(incd_(pasha, leap, 24), WEEK4_AFTER_EASTER_WED);
  set_result_value(incd_(pasha, leap, 25), WEEK4_AFTER_EASTER_THU);
  set_result_value(incd_(pasha, leap, 26), WEEK4_AFTER_EASTER_FRI);
  set_result_value(incd_(pasha, leap, 27), WEEK4_AFTER_EASTER_SAT);
  set_result_value(incd_(pasha, leap, 28), SUN5_AFTER_EASTER);
  set_result_value(incd_(pasha, leap, 29), WEEK5_AFTER_EASTER_MON);
  set_result_value(incd_(pasha, leap, 30), WEEK5_AFTER_EASTER_TUE);
  set_result_value(incd_(pasha, leap, 31), WEEK5_AFTER_EASTER_WED);
  set_result_value(incd_(pasha, leap, 32), WEEK5_AFTER_EASTER_THU);
  set_result_value(incd_(pasha, leap, 33), WEEK5_AFTER_EASTER_FRI);
  set_result_value(incd_(pasha, leap, 34), WEEK5_AFTER_EASTER_SAT);
  set_result_value(incd_(pasha, leap, 35), SUN6_AFTER_EASTER);
  set_result_value(incd_(pasha, leap, 36), WEEK6_AFTER_EASTER_MON);
  set_result_value(incd_(pasha, leap, 37), WEEK6_AFTER_EASTER_TUE);
  set_result_value(incd_(pasha, leap, 38), WEEK6_AFTER_EASTER_WED);
  set_result_value(ascension             , WEEK6_AFTER_EASTER_THU);
  set_result_value(incd_(pasha, leap, 40), WEEK6_AFTER_EASTER_FRI);
  set_result_value(incd_(pasha, leap, 41), WEEK6_AFTER_EASTER_SAT);
  set_result_value(incd_(pasha, leap, 42), SUN7_AFTER_EASTER);
  set_result_value(incd_(pasha, leap, 43), WEEK7_AFTER_EASTER_MON);
  set_result_value(incd_(pasha, leap, 44), WEEK7_AFTER_EASTER_TUE);
  set_result_value(incd_(pasha, leap, 45), WEEK7_AFTER_EASTER_WED);
  set_result_value(incd_(pasha, leap, 46), WEEK7_AFTER_EASTER_THU);
  set_result_value(incd_(pasha, leap, 47), WEEK7_AFTER_EASTER_FRI);
  set_result_value(incd_(pasha, leap, 48), WEEK7_AFTER_EASTER_SAT);
  set_result_value(pentecost             , PENTECOST_SUN);
  set_result_value(incd_(pasha, leap, 50), PENTECOST_MON);
  set_result_value(incd_(pasha, leap, 51), PENTECOST_TUE);
  set_result_value(incd_(pasha, leap, 52), PENTECOST_WED);
  set_result_value(incd_(pasha, leap, 53), PENTECOST_THU);
  set_result_value(incd_(pasha, leap, 54), PENTECOST_FRI);
  set_result_value(incd_(pasha, leap, 55), PENTECOST_SAT);
  set_result_value(all_saints            , SUN1_AFTER_PENTECOST);
  set_result_value(incd_(pasha, leap, 63), SUN2_AFTER_PENTECOST);
  set_result_value(incd_(pasha, leap, 70), SUN3_AFTER_PENTECOST);
  set_result_value(incd_(pasha, leap, 77), SUN4_AFTER_PENTECOST);


  //..
  return result;
}//consteval YearProperties calc_year_properties_for(const int year_number_in_great_indiction)


consteval const auto calc_great_indiction_properties_array()
{
  // index+1 = number of year in great indiction
  std::array<YearProperties, 532> result;
  for (size_t i=0; i<result.size(); ++i) result[i] = calc_year_properties_for(i+1) ;
  return result;
}


constexpr auto great_indiction_properties_array = calc_great_indiction_properties_array() ;



} // namespace


namespace great_indiction {

MonthDay easter_date(const int i)
{
  check_year_number(i) ;
  return easter_dates_array[i-1] ;
}


int apostol_fast_length(const int i)
{
  check_year_number(i) ;
  return apostol_fast_length_array[i-1] ;
}


} // namespace great_indiction
