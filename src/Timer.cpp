/**
 * @file Timer.hpp
 * @author Takashi Michikawa <michikawa@acm.org>
 */
#include <mi/Timer.hpp>

namespace mi
{
        class Timer::Impl
        {
        private:
                Impl ( const Impl& that );
                void operator = ( const Impl& that );
        public:
                Impl ( void )
                {
                        this->init();
                }

                ~Impl ( void )
                {
                }
                int size ( void ) const
                {
                        return static_cast<int> ( this->_keys.size() );
                }

                bool exist ( const std::string& key )
                {
                        return this->_startTime.find ( key ) != this->_startTime.end();
                }

                bool start ( const std::string& key, const clock_time_t t )
                {
                        this->_startTime[ key ] = t;
                        return true;
                }

                bool end ( const std::string& key, const clock_time_t t )
                {
                        this->_time[key] =  std::chrono::duration_cast<std::chrono::milliseconds>( t - this->_startTime[key]).count() * 0.001;
                        this->_keys.push_back ( key ) ;
                        return true;
                }

                double get ( const std::string& key )
                {
                        return this->_time[key];
                }

                std::string  getKey ( const int i ) const
                {
                        return this->_keys.at ( i );

                }

                void init ( void )
                {
                        this->_startTime.clear();
                        this->_time.clear();
                        this->_keys.clear();
                }
        private:
                std::map<std::string, clock_time_t> _startTime;/// Start time.
                std::map<std::string, double> _time; ///< Measured time
                std::vector<std::string>      _keys; ///< Key
        };


        Timer::Timer ( void ) : _impl  ( new Timer::Impl() )
        {
                return;
        }

        Timer::~Timer ( void )
        {
                return;
        }

        void
        Timer::init ( void )
        {
                this->_impl->init();
                return;
        }

        bool
        Timer::start ( const std::string& key )
        {
                if ( this->_impl->exist ( key ) ) {
                        std::cerr << "key " << key << " already exists." << std::endl;
                        return false;
                } else {
                        this->_impl->start ( key, this->get_elapsed_time() );
                        return true;
                }
        }

        bool
        Timer::end ( const std::string& key )
        {
                if ( !this->_impl->exist ( key ) ) {
                        std::cerr << "key " << key << " does not exist." << std::endl;
                        return false;
                } else {
                        this->_impl->end ( key, this->get_elapsed_time() );
                        return true;
                }
        };

        double
        Timer::get ( const std::string& key , const time_format format )
        {
                if ( !this->_impl->exist ( key ) ) {
                        return -1.0;
                }

                const double t0 =  this->_impl->get ( key );

                if      ( format == TIME_SECOND ) {
                        return t0;
                } else if ( format == TIME_MINUTE ) {
                        return t0 / TIMER_MINUTE;
                } else if ( format == TIME_HOUR ) {
                        return t0 / TIMER_MINUTE / TIMER_HOUR;
                } else if ( format == TIME_DAY ) {
                        return t0 / TIMER_MINUTE / TIMER_HOUR / TIMER_DAY;
                } else {
                        return -1.0;        // error
                }
        }


        void
        Timer::print ( const std::string& key, const int digit, const time_format format, std::ostream& out )
        {
                if ( ! this->_impl->exist ( key ) ) {
                        return;        // do nothing if the key does not exist.
                }

                out << this->toString ( key, digit, format ) << std::endl;
                return;
        }

        void
        Timer::printAll ( const int digit, const time_format format, std::ostream& out )
        {
                for ( int i = 0 ; i < this->_impl->size() ; ++i ) {
                        const std::string key = this->_impl->getKey ( i );
                        this->print ( key, digit, format, out );
                }
        }

        std::string
        Timer::toString ( const std::string& key, const int digit, const time_format format )
        {
                if ( !this->_impl->exist ( key ) ) {
                        return std::string ( "NULL" );
                }

                if ( format == TIME_AUTO ) {
                        const double t = this->get ( key, TIME_SECOND );
                        const time_format f = this->estimate_format ( t );
                        return this->toString ( key, digit, f );
                } else {
                        std::stringstream ss;
                        ss << key  << " : "
			   << "\t" << std::setprecision ( digit ) << this->get ( key , format )
			   << "\t" << this->get_format_string ( format );
                        return ss.str();
                }
        }

//        double
	clock_time_t
        Timer::get_elapsed_time ( void ) const
        {
		return std::chrono::high_resolution_clock::now();
        }

        time_format
        Timer::estimate_format ( const double t ) const
        {
                double t0 = t;

                if ( t0 < TIMER_MINUTE ) {
                        return TIME_SECOND;
                }

                t0 *= 1.0 / TIMER_MINUTE;

                if ( t0 < TIMER_HOUR   ) {
                        return TIME_MINUTE;
                }

                t0 *= 1.0 / TIMER_HOUR;

                if ( t0 < TIMER_DAY    ) {
                        return TIME_HOUR;
                }

                t0 *= 1.0 / TIMER_HOUR;
                return TIME_DAY;
        }

        std::string
        Timer::get_format_string ( const time_format format ) const
        {
                if      ( format == TIME_SECOND ) {
                        return std::string ( "[s]" );
                } else if ( format == TIME_MINUTE ) {
                        return std::string ( "[m]" );
                } else if ( format == TIME_HOUR ) {
                        return std::string ( "[h]" );
                } else if ( format == TIME_DAY ) {
                        return std::string ( "[d]" );
                } else {
                        return std::string ( "[?]" );
                }
        }
}

