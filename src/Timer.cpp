/**
 * @file Timer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Timer.hpp>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#else
#include <sys/time.h>
#endif

///Unit of clocks (s) .
#ifdef  __APPLE__
#define SUBSECONDS 1.0e-6
#else // linux
#define SUBSECONDS 1.0e-3
#endif

#include <ctime>

namespace mi {
        class Timer::Impl {
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that );
        public:
                Impl ( void ) {
                }

                ~Impl ( void ) {
                }
                int size ( void ) const {
                        return static_cast<int> ( this->_keys.size() );
                }

                bool exist ( const std::string& key ) {
                        return this->_startTime.find ( key ) != this->_startTime.end();
                }

                bool start ( const std::string& key, const double t ) {
                        this->_startTime[ key ] = t;
                        return true;
                }

                bool end ( const std::string& key, const double t ) {
                        this->_time[key] =  t - this->_startTime[key];
                        this->_keys.push_back ( key ) ;
                        return true;
                }

                double get ( const std::string& key ) {
                        return this->_time[key];
                }

                std::string  getKey ( const int i ) const {
                        return this->_keys.at ( i );
                }

                void init ( void ) {
                        this->_startTime.clear();
                        this->_time.clear();
                        this->_keys.clear();
                }
        private:
                std::map<std::string, double> _startTime;/// Start time.
                std::map<std::string, double> _time; ///< Measured time
                std::vector<std::string>      _keys; ///< Key
        };


        Timer::Timer ( void ) : _impl  ( new Timer::Impl() ) {
                this->init();
                return;
        }
        Timer::~Timer ( void ) {
                return;
        }

        void
        Timer::init ( void ) {
                this->_impl->init();
                return;
        }

        bool
        Timer::start ( const std::string& key ) {
                if ( this->_impl->exist ( key ) ) {
                        std::cerr << "key " << key << " already exists." << std::endl;
                        return false;
                } else {
                        this->_impl->start ( key, this->get_elapsed_time() );
                        return true;
                }
        }

        bool
        Timer::end ( const std::string& key ) {
                if ( !this->_impl->exist ( key ) ) {
                        std::cerr << "key " << key << " does not exist." << std::endl;
                        return false;
                } else {
                        this->_impl->end ( key, this->get_elapsed_time() );
                        return true;
                }
        };

        double
        Timer::get ( const std::string& key , const time_format format ) {
                if ( !this->_impl->exist ( key ) ) return -1.0;
                const double t0 =  this->_impl->get ( key );
                if      ( format == TIME_SECOND ) return t0;
                else if ( format == TIME_MINUTE ) return t0 / TIMER_MINUTE;
                else if ( format == TIME_HOUR )   return t0 / TIMER_MINUTE / TIMER_HOUR;
                else if ( format == TIME_DAY )    return t0 / TIMER_MINUTE / TIMER_HOUR / TIMER_DAY;
                else return -1.0;// error
        }


        void
        Timer::print ( const std::string& key, const int digit, const time_format format, std::ostream& out ) {
                if ( !this->_impl->exist ( key ) ) return;
                out << this->toString ( key, digit, format ) << std::endl;
                return;
        }

        void
        Timer::printAll ( const int digit, const time_format format, std::ostream& out ) {
                for ( int i = 0 ; i < this->_impl->size() ; ++i ) {
                        const std::string key = this->_impl->getKey ( i );
                        this->print ( key, digit, format, out );
                }
        }

        std::string
        Timer::toString ( const std::string& key, const int digit, const time_format format ) {
                if ( !this->_impl->exist ( key ) ) {
                        return std::string ( "NULL" );
                }
                if ( format == TIME_AUTO ) {
                        const double t = this->get ( key, TIME_SECOND );
                        if ( t < TIMER_MINUTE ) {
                                return this->toString ( key, digit, TIME_SECOND );
                        } else if ( t < TIMER_MINUTE * TIMER_HOUR ) {
                                return this->toString ( key, digit, TIME_MINUTE );
                        } else if ( t < TIMER_MINUTE * TIMER_HOUR * TIMER_DAY ) {
                                return this->toString ( key, digit, TIME_HOUR );
                        } else {
                                return this->toString ( key, digit, TIME_DAY );
                        }
                } else {
                        std::stringstream ss;
                        ss << key << " : \t" << std::setprecision ( digit ) << this->get ( key , format ) << "\t";
                        if      ( format == TIME_SECOND ) ss << "[s]";
                        else if ( format == TIME_MINUTE ) ss << "[m]";
                        else if ( format == TIME_HOUR )   ss << "[h]";
                        else if ( format == TIME_DAY )    ss << "[d]";
                        else return std::string();
                        return ss.str();
                }
        }

        double
        Timer::get_elapsed_time ( void ) const {
#ifdef WIN32
                LARGE_INTEGER start_pc, freq_pc;
                QueryPerformanceFrequency ( &freq_pc );
                QueryPerformanceCounter ( &start_pc );
                return static_cast<double> ( start_pc.QuadPart ) / static_cast<double> ( freq_pc.QuadPart );
#else //linux, mac
                struct timeval tv0;
                gettimeofday ( &tv0 , NULL );
                return tv0.tv_sec + tv0.tv_usec * SUBSECONDS;
#endif
        }
}

