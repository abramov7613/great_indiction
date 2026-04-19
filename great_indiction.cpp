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
#include <initializer_list>
#include <tuple>
#include <array>
#include <stdexcept>
#include <algorithm>


namespace {

using namespace great_indiction ;


constexpr void check_year_number(const int year_number_in_great_indiction)
{
  if (year_number_in_great_indiction < 1 || year_number_in_great_indiction > GREAT_INDICTION_LENGTH)
    throw std::runtime_error("value of 'year_number_in_great_indiction' must be in range [1,533)");
}


constexpr bool is_leap(const int year_number_in_great_indiction)
{
  check_year_number(year_number_in_great_indiction) ;
  const int year = year_number_in_great_indiction + 1940 ;
  return (year%4 == 0) ;
}


constexpr int month_length(const int month, const bool leap)
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


constexpr void check_date(const int year_number_in_great_indiction, const MonthDay date)
{
  check_year_number(year_number_in_great_indiction);
  if (date.first < 1 || date.first > 12) throw std::runtime_error("invalid month number");
  if (date.second < 1 || date.second > month_length(date.first, is_leap(year_number_in_great_indiction)))
    throw std::runtime_error("invalid day number");
}


constexpr auto incd_(const MonthDay date, const bool leap, const int days=1)
{
  MonthDay r {date};
  if(days<1) { return date; }
  if(date.first<1 || date.first>12)  { return date; }
  int u = month_length(date.first, leap);
  if(date.second<1 || date.second>u) { return date; }
  r.second += days;
  while (r.second>u) {
    r.second = r.second - u;
    r.first++;
    if(r.first>12) return date;//return source value in this case
    u = month_length(r.first, leap);
  }
  return r;
}


constexpr auto decd_(const MonthDay date, const bool leap, const int days=1)
{
  MonthDay r {date};
  if(days<1) { return date; }
  if(date.first<1 || date.first>12)  { return date; }
  int u = month_length(date.first, leap);
  if(date.second<1 || date.second>u) { return date; }
  r.second = r.second - days;
  while (r.second < 1) {
    r.first--;
    if(r.first<1) return date;//return source value in this case
    u = month_length(r.first, leap);
    r.second = u + r.second;
  }
  return r;
}


consteval int fdiv_(int a, int b)
{//floor division
  return (a - (a < 0 ? b - 1 : 0)) / b;
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


class DD {
public:
  consteval DD(const int y, const int m, const int d) : y_(y), m_(m), d_(d) { check_date(y_, {m_, d_}); }
  consteval DD(const int y, const MonthDay d) : DD(y, d.first, d.second) {}
  consteval auto y() const { return y_; }
  consteval auto m() const { return m_; }
  consteval auto d() const { return d_; }
  consteval auto ymd() const { return std::make_tuple(y_, m_, d_); }
  consteval auto md() const { return MonthDay(m_, d_); }
  consteval auto wd() const { return calc_weekday_for(y_, {m_, d_}); }
  consteval auto l() const { return is_leap(y_); }
  consteval auto ml() const { return month_length(m_, l()); }
  // days from beginning of year
  consteval auto dfb() const { return days_count_from_1jan_to(y_, {m_, d_}); }
  //increment copy
  consteval auto icp(const int c=1) const { auto x = incd_({m_, d_}, l(), c); return DD(y_, x); }
  //decrement copy
  consteval auto dcp(const int c=1) const { auto x = decd_({m_, d_}, l(), c); return DD(y_, x); }
  //increment self
  consteval DD& in(const int c=1)
  {
    auto x = incd_({m_, d_}, l(), c);
    m_ = x.first;
    d_ = x.second;
    return *this;
  }
  //decrement self
  consteval DD& de(const int c=1)
  {
    auto x = decd_({m_, d_}, l(), c);
    m_ = x.first;
    d_ = x.second;
    return *this;
  }
  consteval DD& assign(const std::initializer_list<int> il)
  {
    if (il.size() == 3) {
      y_ = *il.begin();
      m_ = *std::next(il.begin());
      d_ = *std::next(il.begin(),2);
    } else if (il.size() == 2) {
      m_ = *il.begin();
      d_ = *std::next(il.begin());
    } else {
      throw "invalid initializer_list size";
    }
    return *this;
  }
  consteval DD& operator++() { return in(); }
  consteval DD& operator--() { return de(); }
  consteval DD operator++(int) { DD old = *this; operator++(); return old; }
  consteval DD operator--(int) { DD old = *this; operator--(); return old; }
  consteval DD& operator=(const std::initializer_list<int> il) { return assign(il); }
  consteval bool operator==(const DD&) const = default;
  consteval bool operator!=(const DD&) const = default;
  consteval bool operator<(const DD& other) const
  {
    if (y_ < other.y_) return true;
    if (y_ > other.y_) return false;
    return md() < other.md() ;
  }
  consteval bool operator<=(const DD& other) const
  {
    return *this < other || *this == other;
  }
  consteval bool operator>(const DD& other) const
  {
    if (y_ > other.y_) return true;
    if (y_ < other.y_) return false;
    return md() > other.md() ;
  }
  consteval bool operator>=(const DD& other) const
  {
    return *this > other || *this == other;
  }

private:
  int y_, m_, d_;
};


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
  return MonthDay(m_, p);
}


// first index  = DayProperty as integer
// second index = year_number_in_great_indiction - 1
// value        = date as MonthDay
constexpr auto array_of_dates_by_property_and_year = []() consteval {
  std::array<std::array<MonthDay, GREAT_INDICTION_LENGTH>, static_cast<unsigned>(DAY_PROPERTY_ENUM_SIZE_)> r;
  auto set_result_value = [&r](const DD& d, const DayProperty p) consteval {
    r[static_cast<int>(p)][d.y()-1] = d.md();
  };
  for (int year = 1; year <= GREAT_INDICTION_LENGTH; ++year) {
    // точки отсчета
    auto const pasha = DD (year, calc_easter_for(year));
    auto const ascension = pasha.icp(39);
    auto const pentecost = ascension.icp(10);
    auto const all_saints = pentecost.icp(7);
    auto const publican_pharisee = pasha.dcp(70);
    auto const prodigal_son = publican_pharisee.icp(7);
    auto const dread_judgement = publican_pharisee.icp(14);
    auto const forgiveness = publican_pharisee.icp(21);
    auto const lent_begin = forgiveness.icp(1);
    auto const palm_sun = lent_begin.icp(41);
    // Сре́тение Господа Бога и Спаса нашего Иисуса Христа
    DD dd (year,2,2),
      t1 (publican_pharisee.icp(13));
    if (dd >= lent_begin) dd = forgiveness;
    set_result_value(dd, GOD_MEETING);
    if (dd == t1) t1 = publican_pharisee.icp(6);
    set_result_value(t1, MEMORIAL_SAT);
    auto const memorial_sat = t1;
    //Предпразднство Сре́тения
    if(DD x(year, 2, 1); dd != x) {
      if(x == t1) x--;
      set_result_value(x, FOREFEAST_GOD_MEETING);
    }
    //отдание праздника Сре́тения
    t1 = prodigal_son;
    DD t2 (t1.icp(2));
    DD t3 (year, 2, 9);
    if(dd>=t1 && dd<=t2) {
      t3 = t1.icp(5);
    }
    t1 = t2 = t1.icp(3);
    if(dd>=t1 && dd<=t2) {
      t3 = dread_judgement.icp(2);
    }
    t1 = dread_judgement;
    t2 = dread_judgement.icp(1);
    if(dd>=t1 && dd<=t2) {
      t3 = dread_judgement.icp(4);
    }
    t1 = dread_judgement.icp(2);
    t2 = dread_judgement.icp(3);
    if(dd>=t1 && dd<=t2) {
      t3 = dread_judgement.icp(6);
    }
    t1 = dread_judgement.icp(4);
    t2 = dread_judgement.icp(6);
    if(dd>=t1 && dd<=t2) {
      t3 = forgiveness;
    }
    if(dd != forgiveness) {
      if(t3 == memorial_sat) t3--;
      set_result_value(t3, ENDOF_GOD_MEETING);
    }
    //Попразднствa Сретения Господня
    t2 = t1 = dd.icp(1);
    int i = 1;
    if(dd != forgiveness && t3 != t1) {
      do {
        if(t2 == memorial_sat) {
          t2++;
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
        t2++;
        i++;
      } while (t2 != t3);
    }
    // от Недели о мытаре́ и фарисе́е до дня Всех святых.
    set_result_value(publican_pharisee        , PUBLICAN_PHARISEE_SUN);
    set_result_value(prodigal_son             , PRODIGAL_SON_SUN);
    set_result_value(dread_judgement          , DREAD_JUDGEMENT_SUN);
    set_result_value(dread_judgement.icp(1)   , CHEESE_MON);
    set_result_value(dread_judgement.icp(2)   , CHEESE_TUE);
    set_result_value(dread_judgement.icp(3)   , CHEESE_WED);
    set_result_value(dread_judgement.icp(4)   , CHEESE_THU);
    set_result_value(dread_judgement.icp(5)   , CHEESE_FRI);
    set_result_value(dread_judgement.icp(6)   , CHEESE_SAT);
    set_result_value(forgiveness              , CHEESE_SUN);
    set_result_value(lent_begin       , LENT_WEEK1_MON);
    set_result_value(lent_begin.icp(1), LENT_WEEK1_TUE);
    set_result_value(lent_begin.icp(2), LENT_WEEK1_WED);
    set_result_value(lent_begin.icp(3), LENT_WEEK1_THU);
    set_result_value(lent_begin.icp(4), LENT_WEEK1_FRI);
    set_result_value(lent_begin.icp(5), LENT_WEEK1_SAT);
    set_result_value(lent_begin.icp(6), LENT_SUN1);
    set_result_value(lent_begin.icp(7), LENT_WEEK2_MON);
    set_result_value(lent_begin.icp(8), LENT_WEEK2_TUE);
    set_result_value(lent_begin.icp(9), LENT_WEEK2_WED);
    set_result_value(lent_begin.icp(10), LENT_WEEK2_THU);
    set_result_value(lent_begin.icp(11), LENT_WEEK2_FRI);
    set_result_value(lent_begin.icp(12), LENT_WEEK2_SAT);
    set_result_value(lent_begin.icp(13), LENT_SUN2);
    set_result_value(lent_begin.icp(14), LENT_WEEK3_MON);
    set_result_value(lent_begin.icp(15), LENT_WEEK3_TUE);
    set_result_value(lent_begin.icp(16), LENT_WEEK3_WED);
    set_result_value(lent_begin.icp(17), LENT_WEEK3_THU);
    set_result_value(lent_begin.icp(18), LENT_WEEK3_FRI);
    set_result_value(lent_begin.icp(19), LENT_WEEK3_SAT);
    set_result_value(lent_begin.icp(20), LENT_SUN3);
    set_result_value(lent_begin.icp(21), LENT_WEEK4_MON);
    set_result_value(lent_begin.icp(22), LENT_WEEK4_TUE);
    set_result_value(lent_begin.icp(23), LENT_WEEK4_WED);
    set_result_value(lent_begin.icp(24), LENT_WEEK4_THU);
    set_result_value(lent_begin.icp(25), LENT_WEEK4_FRI);
    set_result_value(lent_begin.icp(26), LENT_WEEK4_SAT);
    set_result_value(lent_begin.icp(27), LENT_SUN4);
    set_result_value(lent_begin.icp(28), LENT_WEEK5_MON);
    set_result_value(lent_begin.icp(29), LENT_WEEK5_TUE);
    set_result_value(lent_begin.icp(30), LENT_WEEK5_WED);
    set_result_value(lent_begin.icp(31), LENT_WEEK5_THU);
    set_result_value(lent_begin.icp(32), LENT_WEEK5_FRI);
    set_result_value(lent_begin.icp(33), LENT_WEEK5_SAT);
    set_result_value(lent_begin.icp(34), LENT_SUN5);
    set_result_value(lent_begin.icp(35), LENT_WEEK6_MON);
    set_result_value(lent_begin.icp(36), LENT_WEEK6_TUE);
    set_result_value(lent_begin.icp(37), LENT_WEEK6_WED);
    set_result_value(lent_begin.icp(38), LENT_WEEK6_THU);
    set_result_value(lent_begin.icp(39), LENT_WEEK6_FRI);
    set_result_value(lent_begin.icp(40), LENT_WEEK6_SAT);
    set_result_value(palm_sun          , LENT_SUN7);
    set_result_value(palm_sun.icp(1), LENT_WEEK7_MON);
    set_result_value(palm_sun.icp(2), LENT_WEEK7_TUE);
    set_result_value(palm_sun.icp(3), LENT_WEEK7_WED);
    set_result_value(palm_sun.icp(4), LENT_WEEK7_THU);
    set_result_value(palm_sun.icp(5), LENT_WEEK7_FRI);
    set_result_value(palm_sun.icp(6), LENT_WEEK7_SAT);
    set_result_value(pasha       , EASTER);
    set_result_value(pasha.icp(1), BRIGHT_MON);
    set_result_value(pasha.icp(2), BRIGHT_TUE);
    set_result_value(pasha.icp(3), BRIGHT_WED);
    set_result_value(pasha.icp(4), BRIGHT_THU);
    set_result_value(pasha.icp(5), BRIGHT_FRI);
    set_result_value(pasha.icp(6), BRIGHT_SAT);
    set_result_value(pasha.icp(7), SUN2_AFTER_EASTER);
    set_result_value(pasha.icp(8), WEEK2_AFTER_EASTER_MON);
    set_result_value(pasha.icp(9), WEEK2_AFTER_EASTER_TUE);
    set_result_value(pasha.icp(10), WEEK2_AFTER_EASTER_WED);
    set_result_value(pasha.icp(11), WEEK2_AFTER_EASTER_THU);
    set_result_value(pasha.icp(12), WEEK2_AFTER_EASTER_FRI);
    set_result_value(pasha.icp(13), WEEK2_AFTER_EASTER_SAT);
    set_result_value(pasha.icp(14), SUN3_AFTER_EASTER);
    set_result_value(pasha.icp(15), WEEK3_AFTER_EASTER_MON);
    set_result_value(pasha.icp(16), WEEK3_AFTER_EASTER_TUE);
    set_result_value(pasha.icp(17), WEEK3_AFTER_EASTER_WED);
    set_result_value(pasha.icp(18), WEEK3_AFTER_EASTER_THU);
    set_result_value(pasha.icp(19), WEEK3_AFTER_EASTER_FRI);
    set_result_value(pasha.icp(20), WEEK3_AFTER_EASTER_SAT);
    set_result_value(pasha.icp(21), SUN4_AFTER_EASTER);
    set_result_value(pasha.icp(22), WEEK4_AFTER_EASTER_MON);
    set_result_value(pasha.icp(23), WEEK4_AFTER_EASTER_TUE);
    set_result_value(pasha.icp(24), WEEK4_AFTER_EASTER_WED);
    set_result_value(pasha.icp(25), WEEK4_AFTER_EASTER_THU);
    set_result_value(pasha.icp(26), WEEK4_AFTER_EASTER_FRI);
    set_result_value(pasha.icp(27), WEEK4_AFTER_EASTER_SAT);
    set_result_value(pasha.icp(28), SUN5_AFTER_EASTER);
    set_result_value(pasha.icp(29), WEEK5_AFTER_EASTER_MON);
    set_result_value(pasha.icp(30), WEEK5_AFTER_EASTER_TUE);
    set_result_value(pasha.icp(31), WEEK5_AFTER_EASTER_WED);
    set_result_value(pasha.icp(32), WEEK5_AFTER_EASTER_THU);
    set_result_value(pasha.icp(33), WEEK5_AFTER_EASTER_FRI);
    set_result_value(pasha.icp(34), WEEK5_AFTER_EASTER_SAT);
    set_result_value(pasha.icp(35), SUN6_AFTER_EASTER);
    set_result_value(pasha.icp(36), WEEK6_AFTER_EASTER_MON);
    set_result_value(pasha.icp(37), WEEK6_AFTER_EASTER_TUE);
    set_result_value(pasha.icp(38), WEEK6_AFTER_EASTER_WED);
    set_result_value(ascension    , WEEK6_AFTER_EASTER_THU);
    set_result_value(ascension.icp(1), WEEK6_AFTER_EASTER_FRI);
    set_result_value(ascension.icp(2), WEEK6_AFTER_EASTER_SAT);
    set_result_value(ascension.icp(3), SUN7_AFTER_EASTER);
    set_result_value(ascension.icp(4), WEEK7_AFTER_EASTER_MON);
    set_result_value(ascension.icp(5), WEEK7_AFTER_EASTER_TUE);
    set_result_value(ascension.icp(6), WEEK7_AFTER_EASTER_WED);
    set_result_value(ascension.icp(7), WEEK7_AFTER_EASTER_THU);
    set_result_value(ascension.icp(8), WEEK7_AFTER_EASTER_FRI);
    set_result_value(ascension.icp(9), WEEK7_AFTER_EASTER_SAT);
    set_result_value(pentecost       , PENTECOST_SUN);
    set_result_value(pentecost.icp(1), PENTECOST_MON);
    set_result_value(pentecost.icp(2), PENTECOST_TUE);
    set_result_value(pentecost.icp(3), PENTECOST_WED);
    set_result_value(pentecost.icp(4), PENTECOST_THU);
    set_result_value(pentecost.icp(5), PENTECOST_FRI);
    set_result_value(pentecost.icp(6), PENTECOST_SAT);
    set_result_value(all_saints        , SUN1_AFTER_PENTECOST);
    set_result_value(all_saints.icp(7) , SUN2_AFTER_PENTECOST);
    set_result_value(all_saints.icp(14), SUN3_AFTER_PENTECOST);
    set_result_value(all_saints.icp(21), SUN4_AFTER_PENTECOST);
    //Суббота перед Воздви́жение
    dd = {9,13};
    do {
      if(6 == dd.wd()) {
        set_result_value(dd, SAT_BEFORE_EXALTATION);
        break;
      }
      dd--;
    } while (1);
    //неделя перед Воздви́жение
    dd = {9,13};
    do {
      if(0 == dd.wd()) {
        set_result_value(dd, SUN_BEFORE_EXALTATION);
        break;
      }
      dd--;
    } while (1);
    //Суббота после Воздви́жение
    dd = {9,15};
    do {
      if(6 == dd.wd()) {
        set_result_value(dd, SAT_AFTER_EXALTATION);
        break;
      }
      dd++;
    } while (1);
    //неделя после Воздви́жение
    dd = {9,15};
    do {
      if(0 == dd.wd()) {
        set_result_value(dd, SUN_AFTER_EXALTATION);
        break;
      }
      dd++;
    } while (1);
    // Собор новомучеников и исповедников Церкви Русской
    dd = {1,25};
    i = dd.wd();
    switch (i) {
      case 0: { set_result_value(dd, NEW_MARTYRS_OF_RUSSIA); break; }
      case 1: {}
      case 2: {}
      case 3: { set_result_value(dd.dcp(i), NEW_MARTYRS_OF_RUSSIA); break; }
      case 4: {}
      case 5: {}
      case 6: { set_result_value(dd.icp(7-i), NEW_MARTYRS_OF_RUSSIA); break; }
      default: {}
    };
    // Память святых отцов VII Вселенского Собора.
    dd = {10,11};
    i = dd.wd();
    switch (i) {
      case 0: { set_result_value(dd, FATHERS_ECU_COUNCIL_7); break; }
      case 1: {}
      case 2: {}
      case 3: { set_result_value(dd.dcp(i), FATHERS_ECU_COUNCIL_7); break; }
      case 4: {}
      case 5: {}
      case 6: { set_result_value(dd.icp(7-i), FATHERS_ECU_COUNCIL_7); break; }
      default: {}
    };
    // Димитриевская родительская суббота.
    dd = {10,25};
    do {
      if(dd.wd() == 6 && dd.d() != 22) {
        set_result_value(dd, DIMITRI_SAT);
        break;
      }
      dd--;
    } while (1);
    //нед.св.отец перед рождеством от 18до24 дек.
    dd = {12,24};
    do {
      if(dd.wd() == 0) {
        set_result_value(dd, SUN_BEFORE_CHRISTMAS);
        break;
      }
      dd--;
    } while (1);
    //неделя св.праотец от11до17 дек.
    dd--;
    do {
      if(dd.wd() == 0) {
        set_result_value(dd, HOLY_FOREFATHERS_SUN);
        break;
      }
      dd--;
    } while (1);
    // Суббота перед рождеством
    dd = {12,24};
    do {
      if(dd.wd() == 6) {
        set_result_value(dd, SAT_BEFORE_CHRISTMAS);
        break;
      }
      dd--;
    } while (1);
    // Суббота по Рождестве (типикон стр.380)
    i = DD(year,12,25).wd() ;
    switch(i) {
      case 1: { dd = {12,30}; break; }
      case 2: { dd = {12,29}; break; }
      case 3: { dd = {12,28}; break; }
      case 4: { dd = {12,27}; break; }
      case 5: { dd = {12,26}; break; }
      default: { dd = {12,31}; }
    };
    if ( dd.wd() == 6 ) set_result_value(dd, SAT_AFTER_CHRISTMAS);
    else set_result_value(dd, SAT_AFTER_CHRISTMAS_READINGS);
    // Неделя по Рождестве Христовом
    switch(i) {
      case 1: { dd = {12,31}; break; }
      case 2: { dd = {12,30}; break; }
      case 3: { dd = {12,29}; break; }
      case 4: { dd = {12,28}; break; }
      case 5: { dd = {12,27}; break; }
      default: { dd = {12,26}; }
    };
    if ( dd.wd() == 0 ) {
      set_result_value(dd, SUN_AFTER_CHRISTMAS);
    } else {
      set_result_value(dd, SUN_AFTER_CHRISTMAS_READINGS);
    }
    set_result_value(dd, SAINTS_JOSEPH_DAVID_JAMES);
    // Суббота пред Богоявлением (типикон стр.380)
    if(i==0 || i==1) {
      if (i == 1) dd = {12 ,30}; else dd = {12 ,31};
      if (dd.wd() == 6) set_result_value(dd, SAT_BEFORE_BAPTISM);
      else set_result_value(dd, SAT_BEFORE_BAPTISM_READINGS);
    }
    i = DD ((year==1)?(GREAT_INDICTION_LENGTH):(year-1), 12, 25).wd() ;
    if(!(i==0 || i==1)) {
      switch(i) {
        case 2: { dd = {1 ,5}; break; }
        case 3: { dd = {1 ,4}; break; }
        case 4: { dd = {1 ,3}; break; }
        case 5: { dd = {1 ,2}; break; }
        default: { dd = {1 ,1}; }
      };
      if (dd.wd() == 6) set_result_value(dd, SAT_BEFORE_BAPTISM);
      else set_result_value(dd, SAT_BEFORE_BAPTISM_READINGS);
    }
    // неделя пред Богоявлением (типикон стр.380)
    switch(i) {
      case 3: { dd = {1 ,5}; break; }
      case 4: { dd = {1 ,4}; break; }
      case 5: { dd = {1 ,3}; break; }
      case 6: { dd = {1 ,2}; break; }
      default: { dd = {1 ,1}; }
    };
    if (dd.wd() == 0) set_result_value(dd, SUN_BEFORE_BAPTISM);
    else set_result_value(dd, SUN_BEFORE_BAPTISM_READINGS);
    //Суббота пo Богоявление
    dd = {1 ,7};
    do {
      if(dd.wd() == 6) {
        set_result_value(dd, SAT_AFTER_BAPTISM);
        break;
      }
      dd++;
    } while (1);
    //неделя пo Богоявление
    dd = {1 ,7};
    do {
      if(dd.wd() == 0) {
        set_result_value(dd, SUN_AFTER_BAPTISM);
        break;
      }
      dd++;
    } while (1);
    //Собор 3-x свят. Василия Великого, Григория Богослова и Иоанна Златоустого.
    dd = {1, 30};
    if(dd==memorial_sat || dd==dread_judgement.icp(3) || dd==dread_judgement.icp(5)) dd--;
    set_result_value(dd, CONVENTION_OF_3_HIERARCHS);
    // Первое и второе Обре́тение главы Иоанна Предтечи
    dd = {2, 24};
    if( dd == memorial_sat ||
        dd == dread_judgement.icp(3) ||
        dd == dread_judgement.icp(5) ||
        dd == lent_begin ) dd--;
    if(dd>=lent_begin.icp(1) && dd<=lent_begin.icp(4)) dd = lent_begin.icp(5);
    set_result_value(dd, JOHN_BAPTIST_HEAD_DISCOVERY_1_2);
    // Третье обре́тение главы Предтечи и Крестителя Господня Иоанна
    dd = {5, 25};
    if(dd==pentecost.dcp(1) || dd==all_saints) dd = {5, 23};
    if(dd==pentecost.icp(1)) dd = {5, 26};
    if(dd==pentecost) dd = {5, 22};
    set_result_value(dd, JOHN_BAPTIST_HEAD_DISCOVERY_3);
    // Святых сорока́ мучеников, в Севастийском е́зере мучившихся.
    dd = {3, 9};
    if(dd==lent_begin.icp(23)) dd = {3, 8};
    if(dd==lent_begin.icp(31)) dd = {3, 7};
    if(dd==palm_sun.dcp(1)) dd = {3, 10};
    if(dd>=lent_begin && dd<=lent_begin.icp(4)) dd = lent_begin.icp(5);
    set_result_value(dd, HOLY_FORTY_MARTYRS_OF_SEBASTE);
    // Предпразднство Благовещения Пресвятой Богородицы.
    dd = {3, 24};
    t1 = palm_sun.icp(1);
    t2 = {3, 25};
    if(t2<t1) {
      if(dd==palm_sun.dcp(1)) dd = {3, 22};
      if(dd==lent_begin.icp(31)) dd = {3, 23};
      if(dd==lent_begin.icp(29)) dd = {3, 23};
      set_result_value(dd, FOREFEAST_GOD_MOTHER_ANNUNCIATION);
    }
    //отдание праздника Благовещ́ение
    dd = {3, 26};
    t1 = palm_sun.dcp(1);
    if(dd<t1) {
      set_result_value(dd, ENDOF_GOD_MOTHER_ANNUNCIATION);
    }
    //Вмч. Гео́ргия Победоно́сца. Мц. царицы Александры
    dd = {4, 23};
    t1 = palm_sun.icp(1);
    t2 = pasha;
    if(dd>=t1 && dd<=t2) dd = pasha.icp(1);
    set_result_value(dd, HOLY_GREAT_MARTYR_GEORGE);
    //Святых отец 6-и вселенских соборов
    dd = {7, 16};
    switch (dd.wd()) {
      case 0: {
        set_result_value(dd, FATHERS_ECU_COUNCIL_1_6);
      }
      break;
      case 1: { }
      case 2: { }
      case 3: {
        do {
          dd--;
          if(dd.wd()==0) {
            set_result_value(dd, FATHERS_ECU_COUNCIL_1_6);
            break;
          }
        } while(1);
      }
      break;
      case 4: { }
      case 5: { }
      case 6: {
        do {
          dd++;
          if(dd.wd()==0) {
            set_result_value(dd, FATHERS_ECU_COUNCIL_1_6);
            break;
          }
        } while(1);
      }
      break;
      default: { }
    };
    //...

    // первый день сплошной седмицы
    set_result_value({year,12,25}, SOLID_WEEK_CHRISTMAS);
    set_result_value(pentecost, SOLID_WEEK_PENTECOST);
    set_result_value(dread_judgement.icp(1), SOLID_WEEK_CHEESE);
    set_result_value(publican_pharisee, SOLID_WEEK_PUBLICAN_PHARISEE);
    set_result_value(pasha, SOLID_WEEK_BRIGHT);
    // первый день одного из постов
    set_result_value(lent_begin, GREAT_LENT);
    set_result_value(all_saints.icp(1), APOSTOL_LENT);
    set_result_value({year,11,15}, CHRISTMAS_LENT);
    set_result_value({year,8,1}, ASSUMPTION_LENT);
    // один из трех типов церковных праздников
    set_result_value(pasha, MOVEABLE_FEAST);
    set_result_value({year,1,6}, IMMOVEABLE_FEAST);
    set_result_value({year,1,1}, GREAT_FEAST);
  }
  return r;
}();


// index    = [year_number_in_great_indiction - 1]
// value    = apostol fast length as int
constexpr auto apostol_fast_sizes_array = []() consteval {
  auto calc_apostol_fast_length_for = [p = static_cast<int>(PASHA)](const int y) consteval {
    const int x1 = days_count_from_1jan_to(y, array_of_dates_by_property_and_year[p][y-1]) ;
    const int x2 = days_count_from_1jan_to(y, {6,29}) ;
    return x2 - x1 - 57;
  };
  std::array<int, GREAT_INDICTION_LENGTH> result;
  for (size_t i=0; i<GREAT_INDICTION_LENGTH; ++i) result[i] = calc_apostol_fast_length_for(i+1) ;
  return result;
}();


constexpr std::array IMMOVEABLE_FEAST_DATES_ARRAY = {
  MonthDay{1,6},
  MonthDay{3,25},
  MonthDay{8,6},
  MonthDay{8,15},
  MonthDay{9,8},
  MonthDay{9,14},
  MonthDay{11,21},
  MonthDay{12,25},
};


constexpr std::array GREAT_FEAST_DATES_ARRAY = {
  MonthDay{1,1},
  MonthDay{6,24},
  MonthDay{6,29},
  MonthDay{8,29},
  MonthDay{10,1},
};


constexpr std::array SOLID_WEEK_CHRISTMAS_DATES_ARRAY = {
  MonthDay{1,1},
  MonthDay{1,2},
  MonthDay{1,3},
  MonthDay{1,4},
  MonthDay{12,25},
  MonthDay{12,26},
  MonthDay{12,27},
  MonthDay{12,28},
  MonthDay{12,29},
  MonthDay{12,30},
  MonthDay{12,31},
};


constexpr bool date_is_moveable_feast(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(PALM_SUN)][y-1] ;
  const auto d2 = array_of_dates_by_property_and_year[static_cast<int>(ASCENSION)][y-1] ;
  const auto d3 = array_of_dates_by_property_and_year[static_cast<int>(PENTECOST)][y-1] ;
  return date==d1 || date==d2 || date==d3 ;
}


constexpr bool date_is_immoveable_feast(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(GOD_MEETING)][y-1] ;
  return date==d1 ||
    std::any_of(IMMOVEABLE_FEAST_DATES_ARRAY.begin(), IMMOVEABLE_FEAST_DATES_ARRAY.end(), [date](const auto e){
      return date == e;
    }) ;
}


constexpr bool date_is_great_feast(const int y, const MonthDay date)
{
  check_date(y, date);
  return
    std::any_of(GREAT_FEAST_DATES_ARRAY.begin(), GREAT_FEAST_DATES_ARRAY.end(), [date](const auto e){
      return date == e;
    }) ;
}


constexpr bool date_is_great_lent(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(CHEESE_SUN)][y-1] ;
  const auto d2 = array_of_dates_by_property_and_year[static_cast<int>(PASHA)][y-1] ;
  return date > d1 && date < d2 ;
}


constexpr bool date_is_apostol_lent(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(ALL_SAINTS)][y-1] ;
  const auto d2 = MonthDay(6,29);
  return date > d1 && date < d2 ;
}


constexpr bool date_is_christmas_lent(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = MonthDay(11,14);
  const auto d2 = MonthDay(12,25);
  return date > d1 && date < d2 ;
}


constexpr bool date_is_assumption_lent(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = MonthDay(8,1);
  const auto d2 = MonthDay(8,15);
  return date >= d1 && date < d2 ;
}


constexpr bool date_is_solid_week_bright(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(LENT_WEEK7_SAT)][y-1] ;
  const auto d2 = array_of_dates_by_property_and_year[static_cast<int>(SUN2_AFTER_EASTER)][y-1] ;
  return date > d1 && date < d2 ;
}


constexpr bool date_is_solid_week_christmas(const int y, const MonthDay date)
{
  check_date(y, date);
  return
    std::any_of(SOLID_WEEK_CHRISTMAS_DATES_ARRAY.begin(), SOLID_WEEK_CHRISTMAS_DATES_ARRAY.end(), [date](const auto e){
      return date == e;
    }) ;
}


constexpr bool date_is_solid_week_pentecost(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(PENTECOST)][y-1] ;
  const auto d2 = array_of_dates_by_property_and_year[static_cast<int>(ALL_SAINTS)][y-1] ;
  return date >= d1 && date < d2 ;
}


constexpr bool date_is_solid_week_cheese(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(DREAD_JUDGEMENT_SUN)][y-1] ;
  const auto d2 = array_of_dates_by_property_and_year[static_cast<int>(FORGIVENESS_SUN)][y-1] ;
  return date > d1 && date <= d2 ;
}


constexpr bool date_is_solid_week_publican_pharisee(const int y, const MonthDay date)
{
  check_date(y, date);
  const auto d1 = array_of_dates_by_property_and_year[static_cast<int>(PUBLICAN_PHARISEE_SUN)][y-1] ;
  const auto d2 = array_of_dates_by_property_and_year[static_cast<int>(PRODIGAL_SON_SUN)][y-1] ;
  return date >= d1 && date < d2 ;
}


} // namespace without name


namespace great_indiction {

MonthDay easter_date(const int y)
{
  check_year_number(y) ;
  if (y==3) return {4,11};
  return array_of_dates_by_property_and_year[static_cast<int>(PASHA)][y-1] ;
}


int apostol_fast_length(const int y)
{
  check_year_number(y) ;
  return apostol_fast_sizes_array[y-1] ;
}


bool is_date_of(const int y, const MonthDay d, const DayProperty p)
{
  check_date(y, d);
  switch (p) {
    case MOVEABLE_FEAST: return date_is_moveable_feast(y,d);
    case IMMOVEABLE_FEAST: return date_is_immoveable_feast(y,d);
    case GREAT_FEAST: return date_is_great_feast(y,d);
    case GREAT_LENT: return date_is_great_lent(y,d);
    case APOSTOL_LENT: return date_is_apostol_lent(y,d);
    case CHRISTMAS_LENT: return date_is_christmas_lent(y,d);
    case ASSUMPTION_LENT: return date_is_assumption_lent(y,d);
    case SOLID_WEEK_BRIGHT: return date_is_solid_week_bright(y,d);
    case SOLID_WEEK_CHRISTMAS: return date_is_solid_week_christmas(y,d);
    case SOLID_WEEK_PENTECOST: return date_is_solid_week_pentecost(y,d);
    case SOLID_WEEK_CHEESE: return date_is_solid_week_cheese(y,d);
    case SOLID_WEEK_PUBLICAN_PHARISEE: return date_is_solid_week_publican_pharisee(y,d);
    default: return d == array_of_dates_by_property_and_year[static_cast<int>(p)][y-1] ;
  }
}


MonthDay find_date(const int y, const DayProperty p)
{
  check_year_number(y) ;
  return array_of_dates_by_property_and_year[static_cast<int>(p)][y-1] ;
}


std::vector<MonthDay> find_all_dates(const int y, const DayProperty p)
{
  check_year_number(y) ;
  std::vector<MonthDay> result;
  switch (p) {
    case MOVEABLE_FEAST:
      result.push_back(array_of_dates_by_property_and_year[static_cast<int>(PALM_SUN)][y-1]) ;
      result.push_back(array_of_dates_by_property_and_year[static_cast<int>(ASCENSION)][y-1]) ;
      result.push_back(array_of_dates_by_property_and_year[static_cast<int>(PENTECOST)][y-1]) ;
      break;
    case IMMOVEABLE_FEAST:
      result.push_back(array_of_dates_by_property_and_year[static_cast<int>(GOD_MEETING)][y-1]) ;
      std::copy(IMMOVEABLE_FEAST_DATES_ARRAY.begin(),
                IMMOVEABLE_FEAST_DATES_ARRAY.end(),
                std::back_inserter(result));
      break;
    case GREAT_FEAST:
      std::copy(GREAT_FEAST_DATES_ARRAY.begin(),
                GREAT_FEAST_DATES_ARRAY.end(),
                std::back_inserter(result));
      break;
    case GREAT_LENT:
      for (auto dd = find_date(y,p); date_is_great_lent(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case APOSTOL_LENT:
      for (auto dd = find_date(y,p); date_is_apostol_lent(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case CHRISTMAS_LENT:
      for (auto dd = find_date(y,p); date_is_christmas_lent(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case ASSUMPTION_LENT:
      for (auto dd = find_date(y,p); date_is_assumption_lent(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case SOLID_WEEK_BRIGHT:
      for (auto dd = find_date(y,p); date_is_solid_week_bright(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case SOLID_WEEK_CHRISTMAS:
      for (auto dd = find_date(y,p); date_is_solid_week_christmas(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case SOLID_WEEK_PENTECOST:
      for (auto dd = find_date(y,p); date_is_solid_week_pentecost(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case SOLID_WEEK_CHEESE:
      for (auto dd = find_date(y,p); date_is_solid_week_cheese(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    case SOLID_WEEK_PUBLICAN_PHARISEE:
      for (auto dd = find_date(y,p); date_is_solid_week_publican_pharisee(y,dd); dd = incd_(dd, is_leap(y)) )
        result.push_back(dd) ;
      break;
    default:
      result.push_back(array_of_dates_by_property_and_year[static_cast<int>(p)][y-1]) ;
  }
  return result;
}


} // namespace great_indiction
