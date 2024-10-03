

import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.sql.*;

/**
 *
 * @author matto
 */
public class deleteDifficulty extends HttpServlet {
String name;
PreparedStatement prepStat;
Connection conn;
Statement stat;

       public void init() throws ServletException {
        String url = "jdbc:mysql://localhost:3306/";
        String dbName = "appdev";
        String userName = "root";
        String password = "";
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = (Connection) DriverManager.getConnection(url + dbName, userName, password);
            stat = (Statement) conn.createStatement();
            System.out.println("Connected");
            
        } catch (Exception e) {
            System.err.println(e);
        }
    } // end of init() method


    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html;charset=UTF-8");

        name = request.getParameter("name");

        try {
            String query = "DELETE FROM difficulty WHERE name = (?)";
            prepStat = (PreparedStatement) conn.prepareStatement(query);
            prepStat.setString(1, name);
            prepStat.executeUpdate();
            System.out.println("After deletion");
            try ( PrintWriter out = response.getWriter()) {
                out.println("<!DOCTYPE html>");
                out.println("<html>");
                out.println("<head>");
                out.println("<title>Servlet difficulty Counter</title>");
                out.println("</head>");
                out.println("<body>");
                out.println("<br><br><br><h1>Data Deleted successfully</h1>");
			out.println("<br> <br> <br> <a href=\"index.html\">Home</a>");
                out.println("</body>");
                out.println("</html>");
            }

        } catch (Exception e) {
            System.err.println(e);
            try ( PrintWriter out = response.getWriter()) {
                out.println("<!DOCTYPE html>");
                out.println("<html>");
                out.println("<head>");
                out.println("<title>Servlet difficulty Counter</title>");
                out.println("</head>");
                out.println("<body>");
                out.println("<br><br><br><h1>Error on delete</h1>");
 			out.println("<br> <br> <br> <a href=\"index.html\">Home</a>");
                out.println("</body>");
                out.println("</html>");
            }
        }

    }



    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>

}
