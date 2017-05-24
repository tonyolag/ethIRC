namespace thread
{
    template<typename... Types>
    std::thread make_thread(std::string pName, Types... pArgs)
    {
        log::debug << LOC() << "New Thread: " << pName << log::done;
        std::lock_guard<std::mutex> lock(mutex);
        std::thread thread(pArgs...);
        names[thread.get_id()] = pName;
        return thread;
    }

    template<typename... Types>
    std::thread* make_thread_ptr(std::string pName, Types... pArgs)
    {
        log::debug << LOC() << "New Thread: " << pName << log::done;
        std::lock_guard<std::mutex> lock(mutex);
        std::thread *thread = new std::thread(pArgs...);
        names[thread->get_id()] = pName;
        return thread;
    }
}